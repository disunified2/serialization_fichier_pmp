#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"


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
TEST(SerialOBinaryFileChar, write) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    char value = 'a';
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    char result;
    file >> result;

    EXPECT_EQ(result, 'a');
  }
}
TEST(SerialOBinaryFileFloat, writePositive) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr float value = 123456789.0f;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    float result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789.0f);
  }
}
TEST(SerialOBinaryFileFloat, writeNegative) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr float value = -123456789.0f;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    float result = 0;
    file >> result;

    EXPECT_EQ(result, -123456789.0f);
  }
}
TEST(SerialObinaryFileDouble, writePositive) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr double value = 123456789.0;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    double result = 0;
    file >> result;

    EXPECT_EQ(result, 123456789.0);
  }
}
TEST(SerialObinaryFileDouble, writeNegative) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr double value = -123456789.0;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    double result = 0;
    file >> result;

    EXPECT_EQ(result, -123456789.0);
  }
}
TEST(SerialObinaryFileBool, writeTrue) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr bool value = true;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    bool result;
    file >> result;

    EXPECT_TRUE(result);
  }
}
TEST(SerialOBinaryFileBool, writeFalse) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr bool value = false;
    file << value;
  }
  {
    serial::IBinaryFile file(filename);
    bool result;
    file >> result;

    EXPECT_FALSE(result);
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

TEST(SerialIBinaryFileOperatorTest,floatOperator) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr float value = 0.5;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    float result = 0;
    file >> result;
    printf("%f\n", result);
    EXPECT_EQ(result, 0.5);
  }
}

TEST(SerialIBinaryFileOperatorTest,floatOperatorInfiniteFraction) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr float value = 0.33333334f;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    float result = 0;
    file >> result;
    printf("%f\n", result);
    EXPECT_EQ(result, 0.33333334f);
  }
}

TEST(SerialIBinaryFileOperatorTest,doubleOperator) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr double value = 0.5;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    double result = 0;
    file >> result;

    EXPECT_EQ(result, 0.5);
  }
}

TEST(SerialIBinaryFileOperatorTest,doubleOperatorInfiniteFraction) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr double value = 0.33333334f;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    double result = 0;
    file >> result;

    EXPECT_EQ(result, 0.33333334f);
  }
}

TEST(SerialIBinaryFileOperatorTest,booleanOperatorTrue) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr bool value = true;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    bool result;
    file >> result;

    EXPECT_TRUE(result);
  }
}

TEST(SerialIBinaryFileOperatorTest,booleanOperatorFalse) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    constexpr bool value = false;
    file << value;
  }

  {
    serial::IBinaryFile file(filename);
    bool result;
    file >> result;

    EXPECT_FALSE(result);
  }
}

TEST(SerialIBinaryFileOperatorTest,stringOperator) {
  const std::string filename = "test.txt";
  {
    serial::OBinaryFile file(filename);
    const std::string text = "hello world";
    file << text;
  }

  {
    serial::IBinaryFile file(filename);
    std::string result;
    file >> result;

    EXPECT_EQ(result, "hello world");
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
