#include <gtest/gtest.h>
#include <string>

TEST(Interger_Factorization, testFactor)
{
    std::string str = "hello";

    EXPECT_EQ(str, "hello");
}

int main(int argc, char** argv)
{
  // Calling ros::init(), just to remove unwanted args from command-line.
//  ros::init(argc, argv, "test", ros::init_options::AnonymousName);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
