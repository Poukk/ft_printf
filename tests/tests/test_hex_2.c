#include "../test_ft_printf.h"

void setUp(void) {}

void tearDown(void) {}

void test_ft_printf_hex_upper(void) {
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_len, actual_len;

    expected_len = capture_output(expected, BUFFER_SIZE, printf, "Number in HEX: %X", 255);
    actual_len = capture_output(actual, BUFFER_SIZE, ft_printf, "Number in HEX: %X", 255);

    printf("ft_printf(\"Number in HEX: %%X\", 255)\n");
    printf("Expected: '%s' (len: %d)\n", expected, expected_len);
    printf("Actual  : '%s' (len: %d)\n", actual, actual_len);

    TEST_ASSERT_EQUAL_STRING(expected, actual);
    TEST_ASSERT_EQUAL_INT(expected_len, actual_len);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_printf_hex_upper);
    return UNITY_END();
}
