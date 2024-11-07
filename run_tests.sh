#!/bin/bash

TEST_DIR="tests/tests"
[ ! -d "$TEST_DIR" ] && exit 1

failed_tests=0
test_number=1
PURPLE='\033[0;35m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color
CHECK_MARK="✓"
X_MARK="✗"

for test_file in "$TEST_DIR"/*.c; do
  if [ -f "$test_file" ]; then
    binary_name="test_$(basename "${test_file%.*}")"

    echo -e "${PURPLE}------------- Test $test_number -------------${NC}"
    ((test_number++))

    gcc -Wall -Wextra -Werror \
      src/*.c \
      tests/unity/unity.c \
      tests/capture_output.c \
      "$test_file" \
      -o "$binary_name" 2>/dev/null

    if [ $? -eq 0 ]; then
      # Capture the output and filter it
      output=$(./"$binary_name" | sed -n '/^ft_printf/,/^Actual/p')
      test_result=$(./"$binary_name" | grep -q "PASS" && echo "PASS" || echo "FAIL")

      echo "$output"

      if [ "$test_result" = "PASS" ]; then
        echo -e "Diff: ${GREEN}${CHECK_MARK}${NC}"
      else
        echo -e "Diff: ${RED}${X_MARK}${NC}"
        ((failed_tests++))
      fi

      rm "$binary_name"
    else
      echo -e "Diff: ${RED}${X_MARK} (Compilation Failed)${NC}"
      ((failed_tests++))
    fi
  fi
done

exit $failed_tests
