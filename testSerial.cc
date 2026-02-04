#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
