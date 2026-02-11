#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"

TEST(SerialTest, firstTest) {

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