#include "../test_ft_printf.h"

void setUp(void) {}

void tearDown(void) {}


void test_ft_printf_zero_decimal(void) {
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_len, actual_len;

    expected_len = capture_output(expected, BUFFER_SIZE, printf, "%d", 0);
    actual_len = capture_output(actual, BUFFER_SIZE, ft_printf, "%d", 0);

    printf("ft_printf(\"%%d\", 0)\n");
    printf("Expected: '%s' (len: %d)\n", expected, expected_len);
    printf("Actual  : '%s' (len: %d)\n", actual, actual_len);

    TEST_ASSERT_EQUAL_STRING(expected, actual);
    TEST_ASSERT_EQUAL_INT(expected_len, actual_len);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_printf_zero_decimal);
    return UNITY_END();
}
