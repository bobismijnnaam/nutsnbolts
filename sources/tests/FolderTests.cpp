// File: FolderTests.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 20150714
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <iostream>
#include <algorithm>

// Private
#include "catch.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/constants.hpp"

TEST_CASE("Directory functionality", "[dir]") {
    SECTION("Recursive file discovery") {
        auto allFiles = nnb::getFilesRecursively("testfolder" + nnb::DIRSEP);

        std::sort(allFiles.begin(), allFiles.end());

        std::vector<std::string> expected{
                "a",
                "testfolder1" + nnb::DIRSEP + "b",
                "testfolder1" + nnb::DIRSEP + "testfolder2" + nnb::DIRSEP + "c",
                "testfolder2" + nnb::DIRSEP + "d"
        };

        CHECK(allFiles == expected);
    }
}
