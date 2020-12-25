#include <exception>

#include <gtest/gtest.h>
#include "../dctorrent-cli/App.hpp"



void newApp(){
    App app;
}

TEST(dctorrentCli,notExsitsDctorrent){

    App* app = nullptr;
    auto fun = []{App app;};
    ASSERT_THROW(fun(),boost::process::process_error);


}


int main(int argc, char** argv){


    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
