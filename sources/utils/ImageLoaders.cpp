// File: ImageLoaders.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-11
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <stdio.h>
#include <png.h>
#include <jpeglib.h>

// Private
#include "nnb/utils/ImageLoaders.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/log/log.hpp"

namespace nnb {

	std::unique_ptr<unsigned char[]> readPng(std::string file, int *imgWidth, int *imgHeight) {
		if (!nnb::exists(file)) {
			NNB_ERROR << "File not found: " << file;
			return nullptr;
		}

		// Open the file
		FILE *fp = fopen(file.c_str(), "rb");
		if (!fp) {
			NNB_ERROR << "Could not open file: " << file;
			return nullptr;
		}
		
		// Read the 8 byte header
		std::unique_ptr<unsigned char[]> header(new unsigned char[8]);
		int readBytes = fread(header.get(), 1, 8, fp);
		if (readBytes != 8) {
			NNB_ERROR << "Unable to read 8 bytes from file: " << file << ", but read: " << readBytes;
		}

		// Check if according to the header the file is a png file
		// Abort if not
		auto is_png = !png_sig_cmp(header.get(), 0, 8);
		if (!is_png) {
			fclose(fp);
			NNB_ERROR << "File was not a png: " << file;
			return nullptr;
		}

		// Allocate structures needed for reading a png.
		// NULL means use default error/warning structure/function
		png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
		if (!png_ptr) {
			NNB_ERROR << "Failed to create png read struct";
			return nullptr;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			NNB_ERROR << "Failed to create png info struct";
			return nullptr;
		}

		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info) {
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			NNB_ERROR << "Failed to create png end struct";
			return nullptr;
		}

		// Set error handling
		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			NNB_ERROR << "An error occurred while reading png file: " << file;
			return nullptr;
		}

		png_init_io(png_ptr, fp);

		// Inform libpng about header checking
		png_set_sig_bytes(png_ptr, 8);

		png_read_info(png_ptr, info_ptr);
	
		// Get image information
		png_uint_32 width, height;
		int bit_depth, color_type, interlace_type, compression_type, filter_type;
		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);

		// Convert palette to rgb
		if (color_type == PNG_COLOR_TYPE_PALETTE && bit_depth <= 8) png_set_palette_to_rgb(png_ptr);

		// Convert grayscale to rgb
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);

		// Convert tRNS to rgb
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);

		// Make sure 16 bit images are stripped down to 8 bits
		if (bit_depth == 16) png_set_strip_16(png_ptr);

		// Expand for example 8 pixels per byte for 1 bit per pixel to 1 pixel per byte
		if (bit_depth < 8) png_set_packing(png_ptr);

		// Adds an opaque alpha channel if it's not there
		if (bit_depth == 8 && color_type == PNG_COLOR_TYPE_RGB) png_set_filler(png_ptr, 255, PNG_FILLER_AFTER);
		
		// Converts grayscale to RGB
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png_ptr);
		
		png_read_update_info(png_ptr, info_ptr);

		// Allocate memory as a chunk and split it up into 10 ptrs
		std::unique_ptr<unsigned char[]> img(new unsigned char[width * height * 4]);
		std::unique_ptr<png_bytep> row_pointers(new png_bytep[height]);
		for (int i = 0; i < height; ++i) {
			row_pointers.get()[i] = img.get() + i * width * 4;
		}

		png_read_image(png_ptr, row_pointers.get());

		png_read_end(png_ptr, end_info);

		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		// Return width and height of loaded image
		*imgWidth = width;
		*imgHeight = height;

		return std::move(img);
	}

	bool writePng(unsigned char * buffer, int width, int height, std::string file) {
		FILE *fp = fopen(file.c_str(), "wb");
		if (!fp) {
			NNB_ERROR << "Could not open file: " << file;
			return false;
		}

		// Create libpng structs
		png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
		if (!png_ptr) {
			NNB_ERROR << "Could not construct png struct";
			return false;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			NNB_ERROR << "Could not construct info struct";
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			return false;
		}

		// Libpng error mechanism
		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_write_struct(&png_ptr, &info_ptr);
			fclose(fp);
			NNB_ERROR << "An error occurred while writing the png";
			return false;
		}

		png_init_io(png_ptr, fp);

		// Set png output information
		png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		png_write_info(png_ptr, info_ptr);

		// Split up the array in row pointers
		std::unique_ptr<png_bytep[]> row_pointers(new png_bytep[height]);
		for (int y = 0; y < height; ++y) {
			row_pointers.get()[y] = buffer + y * 4 * width;
		}

		png_write_image(png_ptr, row_pointers.get());
		
		// Clean up the structs and close the file
		png_write_end(png_ptr, NULL);

		png_destroy_write_struct(&png_ptr, &info_ptr);

		fclose(fp);

		return true;
	}

	////////////////////////////////
	// JPEG loader helper classes //
	////////////////////////////////

	struct ErrorManager {
		jpeg_error_mgr defaultErrorManager;
		jmp_buf jumpBuffer;
	} ;

	void errorExit(j_common_ptr cinfo) {
		NNB_ERROR << "HALP";
		ErrorManager *errorManager = (ErrorManager*) cinfo->err;
		(*cinfo->err->output_message)(cinfo);
		longjmp(errorManager->jumpBuffer, 1);
	}

	void outputMessage(j_common_ptr cinfo) {
		NNB_ERROR << "HALP";
		char buffer[JMSG_LENGTH_MAX];
		(*cinfo->err->format_message) (cinfo, buffer);
		NNB_ERROR << "JPEG loading error: " << buffer;
	}

	std::unique_ptr<unsigned char[]> readJpeg(std::string file, int *imgWidth, int *imgHeight) {
		if (!nnb::exists(file)) {
			NNB_ERROR << "File not found: " << file;
			return nullptr;
		}

		FILE* fp = fopen(file.c_str(), "rb");
		if (!fp) {
			NNB_ERROR << "Unable to open file: " << file;
			return nullptr;
		}

		// Set up jpeg object and install custom error manager
		jpeg_decompress_struct cinfo;
		ErrorManager em;
		cinfo.err = jpeg_std_error(&em.defaultErrorManager);
		em.defaultErrorManager.error_exit = errorExit;
		em.defaultErrorManager.output_message = outputMessage;

		// Error catching mechanism
		if (setjmp(em.jumpBuffer)) {
			jpeg_destroy_decompress(&cinfo);
			fclose(fp);
			NNB_ERROR << "An error occurred while reading file: " << file;
			return nullptr;
		}

		// Create jpeg object
		jpeg_create_decompress(&cinfo);

		// Set file as input
		jpeg_stdio_src(&cinfo, fp);

		jpeg_read_header(&cinfo, TRUE);

		// Force RGB output colorspace
		cinfo.out_color_space = JCS_RGB;

		jpeg_start_decompress(&cinfo);

		// Allocate buffers for reading the image
		int w = cinfo.output_width;
		int h = cinfo.output_height;
		std::unique_ptr<unsigned char[]> img(new unsigned char[cinfo.output_width * cinfo.output_height * 4]);
		std::unique_ptr<unsigned char[]> scanline(new unsigned char[cinfo.output_width * 3]);
		unsigned char* scanlinePtr = scanline.get();
		int nextRow = 0;

		while(cinfo.output_scanline < cinfo.output_height) {
			if (jpeg_read_scanlines(&cinfo, &scanlinePtr, 1) == 1) {
				for (int x = 0; x < w; ++x) {
					// Add an alpha channel to the pixel and copy it over to my buffer
					img.get()[nextRow * w * 4 + x * 4] = scanline.get()[x * 3];
					img.get()[nextRow * w * 4 + x * 4 + 1] = scanline.get()[x * 3 + 1];
					img.get()[nextRow * w * 4 + x * 4 + 2] = scanline.get()[x * 3 + 2];
					img.get()[nextRow * w * 4 + x * 4 + 3] = 255;
				}
				
				nextRow++;
			}
		}

		// Clean up
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		// Export the image size
		*imgWidth = w;
		*imgHeight = h;

		return std::move(img);
	}

	bool writeJpeg(unsigned char * buffer, int width, int height, std::string file, int quality) {
		FILE* fp = fopen(file.c_str(), "wb");
		if (!fp) {
			NNB_ERROR << "Unable to open file: " << file;
			return false;
		}

		// Set up jpeg object and install custom error manager
		jpeg_compress_struct cinfo;
		ErrorManager em;
		cinfo.err = jpeg_std_error(&em.defaultErrorManager);
		em.defaultErrorManager.error_exit = errorExit;
		em.defaultErrorManager.output_message = outputMessage;

		// Error catching mechanism
		if (setjmp(em.jumpBuffer)) {
			jpeg_destroy_compress(&cinfo);
			fclose(fp);
			NNB_ERROR << "An error occurred while writing to file: " << file;
			return false;
		}

		jpeg_create_compress(&cinfo);

		// Set output file
		jpeg_stdio_dest(&cinfo, fp);

		// Set output parameters
		cinfo.image_width = width; 
		cinfo.image_height = height;
		cinfo.input_components = 3;
		cinfo.in_color_space = JCS_RGB;

		// Deduce defaults from input parameters
		jpeg_set_defaults(&cinfo);

		jpeg_set_quality(&cinfo, quality, FALSE);

		jpeg_start_compress(&cinfo, TRUE);

		// Output scanline buffer
		std::unique_ptr<unsigned char[]> scanline(new unsigned char[width * 3]);
		unsigned char *scanlinePtr = scanline.get();

		// Strip the alpha channel from each row and write it to the file
		while (cinfo.next_scanline < cinfo.image_height) {
			for (int x = 0; x < width; ++x) {
				scanlinePtr[x * 3] = buffer[width * 4 * cinfo.next_scanline  + x * 4];
				scanlinePtr[x * 3 + 1] = buffer[width * 4 * cinfo.next_scanline  + x * 4 + 1];
				scanlinePtr[x * 3 + 2] = buffer[width * 4 * cinfo.next_scanline  + x * 4 + 2];
			}

			jpeg_write_scanlines(&cinfo, &scanlinePtr, 1);
		}

		// Clean up
		jpeg_finish_compress(&cinfo);
		jpeg_destroy_compress(&cinfo);

		fclose(fp);

		return true;
	}

}
