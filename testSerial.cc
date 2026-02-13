#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"

TEST(SerialTest, firstTest) {

}

// Constructor tests, works both for OBinaryFile and IBinaryFile
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
TEST(SerialOBinaryFileUint16, write) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint16_t value = 65535u;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    uint16_t result = 0;
    file >> result;

    EXPECT_EQ(result, 65535u);
  }
}
TEST(SerialOBinaryFileInt16, writePositive) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint16_t value = 32767;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    uint16_t result = 0;
    file >> result;

    EXPECT_EQ(result, 32767);
  }
}
TEST(SerialOBinaryFileInt16, writeNegative) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr int16_t value = -32767;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    int16_t result = 0;
    file >> result;

    EXPECT_EQ(result, -32767);
  }
}
TEST(SerialOBinaryFileUint32, write) {
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
TEST(SerialOBinaryFileInt32, writePositive) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr int32_t value = 123456789;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    int32_t result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789);
  }
}
TEST(SerialOBinaryFileInt32, writeNegative) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr int32_t value = -123456789;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    int32_t result = 0;
    file >> result;

    EXPECT_EQ(result, -123456789);
  }
}
TEST(SerialOBinaryFileUint64, write) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint64_t value = 123456789u;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    uint64_t result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789u);
  }
}
TEST(SerialOBinaryFileUint64, writePositive) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr int64_t value = 123456789;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    int64_t result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789);
  }
}
TEST(SerialOBinaryFileUint64, writeNegative) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr int64_t value = -123456789;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    int64_t result = 0;
    file >> result;

    EXPECT_EQ(result, -123456789);
  }
}

TEST(SerialIBinaryFileConstructorTest,MoveConstructorTest) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint32_t value = 123456789u;
    file << value;
  }

  {
    serial::IBinaryFile f1("test.txt");
    serial::IBinaryFile f2(std::move(f1));
    uint32_t result = 0;
    f2 >> result;
    EXPECT_EQ(result, 123456789u);
  }
}

TEST(SerialIBinaryFileConstructorTest, MoveAssignmentTest) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr uint32_t value = 123456789u;
    file << value;
  }
  {
    serial::IBinaryFile f1(filename);
    serial::IBinaryFile f2 = std::move(f1);
    uint32_t result = 0;
    f2 >> result;

    EXPECT_EQ(result, 123456789u);
  }
}

TEST(SerialIBinaryFileOperatorTest,uint8_tOperator) {
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
