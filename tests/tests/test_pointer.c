#include "../test_ft_printf.h"

void setUp(void) {}

void tearDown(void) {}

void test_ft_printf_pointer(void) {
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_len, actual_len;
    int number = 42;
    void *ptr = &number;

    expected_len = capture_output(expected, BUFFER_SIZE, printf, "%p", ptr);
    actual_len = capture_output(actual, BUFFER_SIZE, ft_printf, "%p", ptr);

    printf("ft_printf(\"%%p\", ptr)\n");
    printf("Expected: '%s' (len: %d)\n", expected, expected_len);
    printf("Actual  : '%s' (len: %d)\n", actual, actual_len);

    TEST_ASSERT_EQUAL_STRING(expected, actual);
    TEST_ASSERT_EQUAL_INT(expected_len, actual_len);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_printf_pointer);
    return UNITY_END();

}
