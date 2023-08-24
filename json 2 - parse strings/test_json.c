#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "miniunit.h"

static int _test_parse_int_single_zero()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "0";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 1);
    mu_check(result == 0);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_single_char()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "A";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(!is_success);  // because the input is valid
    mu_check(pos == input); // failure should be at the first character in the input
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_negative_zero()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-0";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 2);
    mu_check(result == 0);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_negative_single_char()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-A";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(!is_success);      // because the input is valid
    mu_check(pos == input + 1); // failure should be at the first character in the input, not the negative sign
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_full_string()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "AAABBBCCC";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(!is_success); // because the input is valid
    mu_check(pos == input);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_negative_string_with_numbers()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-ABC123";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(!is_success); // because the input is valid
    mu_check(pos == input + 1);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_full_number()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "123456789";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 9);
    mu_check(result == 123456789);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_number_with_string()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "123ABC";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 3);
    mu_check(result == 123);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_negative_number_with_string()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-123ABC";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 4);
    mu_check(result == -123);
    // ──────────────────────────────────────────────────────
    mu_end();
}
static int _test_parse_int_negative_number_with_string_and_number()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-123ABC456";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 4);
    mu_check(result == -123);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_int_negative_number_with_string_and_number_and_negative_number()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    int result; // will be initialized in parse_int(…)
    char *input = "-123ABC-456";
    char const *pos = input;
    bool is_success = parse_int(&result, &pos);
    mu_check(is_success); // because the input is valid
    mu_check(pos == input + 4);
    mu_check(result == -123);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_int_plain()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char *input = "1";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_INT);
    mu_check(element.as_int == 1);
    mu_check(pos == input + 1);
    mu_check(*pos == '\0');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_int_negative()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char *input = "-2";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_INT);
    mu_check(element.as_int == -2);
    mu_check(pos == input + 2);
    mu_check(*pos == '\0');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_int_with_leading_whitespace()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char *input = "  1"; // two spaces before the 1
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_INT);
    mu_check(element.as_int == 1);
    mu_check(pos == input + 3);
    mu_check(*pos == '\0');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_int_oddballs()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char *input = " 4 A";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_INT);
    mu_check(element.as_int == 4);
    mu_check(pos == input + 2);
    mu_check(*pos == ' ');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_int_invalid()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char *input = "--4";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(!is_success);
    mu_check(pos == input + 1);
    mu_check(*pos == '-');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_valid_empty()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("", result);
    mu_check(pos == input + 2);
    mu_check(*pos == '\0');
    free(result);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_valid_one_char()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"A\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("A", result);
    mu_check(pos == input + 3);
    mu_check(*pos == '\0');
    free(result);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_valid_multiple_chars()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"ABC\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("ABC", result);
    mu_check(pos == input + 5);
    mu_check(*pos == '\0');
    free(result);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_invalid()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"A";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(!is_success);
    mu_check(pos == input + 2);
    mu_check(*pos == '\0');

    input = "\"A\nB\"";
    pos = input;
    is_success = parse_string(&result, &pos);
    mu_check(!is_success);
    mu_check(pos == input + 2);
    mu_check(*pos == '\n');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_quote_in_middle()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"A\"B\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("A", result);
    mu_check(pos == input + 3);
    mu_check(*pos == 'B');
    free(result);
    // ──────────────────────────────────────────────────────
    mu_end();
}

// More test for parse_string to get 100% coverage:

static int _test_parse_string_valid_with_escaped_characters()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"A\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("A", result);
    mu_check(pos == input + 3);
    mu_check(*pos == '\0');
    free(result);

    input = "\"A\\nB\""; // same as: {'\"', 'A', '\\', 'n', 'B', '\"'}
    pos = input;
    is_success = parse_string(&result, &pos);
    mu_check(is_success);
    mu_check_strings_equal("A\\nB", result);
    mu_check(pos == input + 6);
    mu_check(*pos == '\0');
    free(result);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_tab_escape_char()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "\"A\tB\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(!is_success);
    mu_check(pos == input + 2);
    mu_check(*pos == '\t');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_string_first_char_not_doubtle_quote()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    char *result;
    char *input = "A\"";
    char const *pos = input;
    bool is_success = parse_string(&result, &pos);
    mu_check(!is_success);
    mu_check(pos == input);
    mu_check(*pos == 'A');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_string()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "\"ABC\"";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_STRING);
    mu_check_strings_equal("ABC", element.as_string);
    mu_check(pos == input + 5);
    mu_check(*pos == '\0');
    free_element(element);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_string_long()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "\"Hello, World!\"";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_STRING);
    mu_check_strings_equal("Hello, World!", element.as_string);
    mu_check(pos == input + 15);
    mu_check(*pos == '\0');
    free_element(element);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_string_num_str()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "\"12345\"";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_STRING);
    mu_check_strings_equal("12345", element.as_string);
    mu_check(pos == input + 7);
    mu_check(*pos == '\0');
    free_element(element);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_string_empty()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "\"\"";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_STRING);
    mu_check_strings_equal("", element.as_string);
    mu_check(pos == input + 2);
    mu_check(*pos == '\0');
    free_element(element);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_string_more_escape_chars()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "\"Escape \\\"characters\\\"\"";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(is_success);
    mu_check(element.type == ELEMENT_STRING);
    mu_check_strings_equal("Escape \\", element.as_string);
    mu_check(pos == input + 10);
    mu_check(*pos == 'c');
    free_element(element);
    // ──────────────────────────────────────────────────────
    mu_end();
}

static int _test_parse_element_does_not_call_any_parse_func()
{
    mu_start();
    // ──────────────────────────────────────────────────────
    Element element;
    char const *input = "ABC";
    char const *pos = input;
    bool is_success = parse_element(&element, &pos);
    mu_check(!is_success);
    mu_check(pos == input);
    mu_check(*pos == 'A');
    // ──────────────────────────────────────────────────────
    mu_end();
}

static void _test_print_element()
{
    Element element;
    char const *input = "123";
    bool is_success = parse_element(&element, &input);
    printf("issucces: %s", is_success ? "true" : "false");
    printf("Testing parse element(&element, \"123\")\n");
    printf(" - Expected: 123\n");
    printf(" - Actual:   ");
    print_element(element);
    fputc('\n', stdout);
    free_element(element);
}

static void _test_print_element_2()
{
    Element element;
    char const *input = "\"ABC\"";
    bool is_success = parse_element(&element, &input);
    printf("issucces: %s", is_success ? "true" : "false");
    printf("Testing parse element(&element, \"\\\"ABC\\\"\")\n");
    printf(" - Expected: \"ABC\"\n");
    printf(" - Actual:   ");
    print_element(element);
    fputc('\n', stdout);
    free_element(element);
}

int main(int argc, char *argv[])
{
    mu_run(_test_parse_int_single_zero);
    mu_run(_test_parse_int_single_char);
    mu_run(_test_parse_int_negative_zero);
    mu_run(_test_parse_int_negative_single_char);
    mu_run(_test_parse_int_full_string);
    mu_run(_test_parse_int_negative_string_with_numbers);
    mu_run(_test_parse_int_full_number);
    mu_run(_test_parse_int_number_with_string);
    mu_run(_test_parse_int_negative_number_with_string);
    mu_run(_test_parse_int_negative_number_with_string_and_number);
    mu_run(_test_parse_int_negative_number_with_string_and_number_and_negative_number);

    mu_run(_test_parse_element_int_plain);
    mu_run(_test_parse_element_int_negative);
    mu_run(_test_parse_element_int_with_leading_whitespace);
    mu_run(_test_parse_element_int_oddballs);
    mu_run(_test_parse_element_int_invalid);

    mu_run(_test_parse_string_valid_empty);
    mu_run(_test_parse_string_valid_one_char);
    mu_run(_test_parse_string_valid_multiple_chars);
    mu_run(_test_parse_string_invalid);
    mu_run(_test_parse_string_quote_in_middle);
    mu_run(_test_parse_string_valid_with_escaped_characters);
    mu_run(_test_parse_string_tab_escape_char);
    mu_run(_test_parse_string_first_char_not_doubtle_quote);

    mu_run(_test_parse_element_string);
    mu_run(_test_parse_element_string_long);
    mu_run(_test_parse_element_string_num_str);
    mu_run(_test_parse_element_string_empty);
    mu_run(_test_parse_element_string_more_escape_chars);
    mu_run(_test_parse_element_does_not_call_any_parse_func);
    _test_print_element();
    _test_print_element_2();

    return EXIT_SUCCESS;
}
