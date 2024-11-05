#!/bin/bash

TEST_DIR="tests/tests"
[ ! -d "$TEST_DIR" ] && exit 1

failed_tests=0
test_number=1
PURPLE='\033[0;35m'
NC='\033[0m' # No Color

for test_file in "$TEST_DIR"/*.c; do
  if [ -f "$test_file" ]; then
    binary_name="test_$(basename "${test_file%.*}")"

    echo -e "${PURPLE}--------- Test $test_number ---------${NC}"
    ((test_number++))

    gcc \
      -Wall -Wextra -Werror \
      src/printf.c \
      tests/unity/unity.c \
      tests/capture_output.c \
      "$test_file" \
      -o "$binary_name" 2>/dev/null

    if [ $? -eq 0 ]; then
      ./"$binary_name"
      [ $? -ne 0 ] && ((failed_tests++))
      rm "$binary_name"
    else
      ((failed_tests++))
    fi
  fi
done

exit $failed_tests
