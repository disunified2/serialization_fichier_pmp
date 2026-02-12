#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"

TEST(SerialTest, firstTest) {

}

// Constructor tests
TEST(SerialOBinaryFileConstructorTest, BasicConstructorTest) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint32_t value = 123456789u;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    uint32_t result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789u);
  }
}
TEST(SerialOBinaryFileConstructorTest, MoveConstructorTest) {
  {
    serial::OBinaryFile f1("test.txt");
    serial::OBinaryFile f2(std::move(f1));
    constexpr uint32_t value = 123456789u;
    f2 << value;
  }
  {
    serial::IBinaryFile f2("test.txt");
    uint32_t result = 0;
    f2 >> result;

    EXPECT_EQ(result, 123456789u);
  }
}
TEST(SerialOBinaryFileConstructorTest, MoveAssignmentTest) {
  {
    serial::OBinaryFile f1("test.txt");
    serial::OBinaryFile f2 = std::move(f1);
    constexpr uint32_t value = 123456789u;
    f2 << value;
  }
  {
    serial::IBinaryFile f2("test.txt");
    uint32_t result = 0;
    f2 >> result;

    EXPECT_EQ(result, 123456789u);
  }
}

TEST(IBinaryFileOperatorTest,uint8_tOperator) {
  /*
  uint8_t x = 0;

  serial::IBinaryFile f("test.bin");
  f >> x;

  EXPECT_EQ(x, 42);
  */
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
