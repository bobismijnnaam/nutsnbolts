// File: GameFrame.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 16-10-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMEFRAME_HPP
#define NNB_GAMEFRAME_HPP

// Public
#include <SDL2/SDL.h>
#include <stack>
#include <deque>
#include <memory>

// Private


namespace nnb {


	class Subsystem {
	public:
		Subsystem(std::string name_);
        virtual ~Subsystem() = default;

		virtual bool init() = 0;
		virtual bool quit() = 0;
		virtual std::string getError();
		virtual std::string getName();

	protected:
		std::string error;
		std::string name;
	} ;

	class SDLSubsystem : public Subsystem {
	public:
		SDLSubsystem(Uint32 flags_);

		virtual bool init() override;
		virtual bool quit() override;
	
	private:
		Uint32 flags;
	} ;

	class SDL_ImageSubsystem : public Subsystem {
	public:
		SDL_ImageSubsystem(int flags_);

		virtual bool init() override;
		virtual bool quit() override;

	private:
		int flags;
	} ;

	class SDL_TTFSubsystem : public Subsystem {
	public:
		SDL_TTFSubsystem();
		virtual bool init() override;
		virtual bool quit() override;
	} ;

	class SDL_MixerSubsystem : public Subsystem {
	public:
		SDL_MixerSubsystem(int flags_);

		virtual bool init() override;
		virtual bool quit() override;

	private:
		int flags;
	} ;

	class GameFrame {
	public:
		GameFrame();

		void giveSDL(bool timer, bool audio, bool video);
		void giveSDL(Uint32 flags);

		void giveSDL_Image(bool jpg, bool png, bool tif);
		void giveSDL_Image(int flags);

		void giveSDL_TTF();

		void giveSDL_Mixer(bool flac, bool mod, bool mp3, bool ogg);
		void giveSDL_Mixer(int flags);
		
		void give(std::unique_ptr<Subsystem> ss);
		
		bool launch();
		bool land();
		std::string getError();
		bool getSuccess();

	private:
		std::deque<std::unique_ptr<Subsystem>> queue;
		std::stack<std::unique_ptr<Subsystem>> active;
		std::string errorMsg;
		bool success;
	} ;

}

#endif

