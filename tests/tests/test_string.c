#include "../test_ft_printf.h"

void setUp(void) {}

void tearDown(void) {}

void test_ft_printf_string(void) {
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_len, actual_len;

    expected_len = capture_output(expected, BUFFER_SIZE, printf, "Hello, %s!", "World");
    actual_len = capture_output(actual, BUFFER_SIZE, ft_printf, "Hello, %s!", "World");

	printf("printf(\"Hello, %%s!\", \"World\")\n");
    printf("Expected: '%s' (len: %d)\n", expected, expected_len);
    printf("Actual  : '%s' (len: %d)\n", actual, actual_len);

    TEST_ASSERT_EQUAL_STRING(expected, actual);
    TEST_ASSERT_EQUAL_INT(expected_len, actual_len);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_printf_string);
    return UNITY_END();

}
