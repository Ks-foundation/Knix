#include "kinxlib.h"

void main() {
    char input[100];
    int num1, num2;
    char operator;
    int result;

    // 사용자에게 첫 번째 숫자 입력을 요청
    print_string("Enter the first number: ");
    read_input(input, sizeof(input));
    num1 = atoi(input);

    // 사용자에게 연산자 입력을 요청
    print_string("Enter the operator (+, -, *, /): ");
    operator = get_char();
    print_char(operator);
    print_string("\n");

    // 사용자에게 두 번째 숫자 입력을 요청
    print_string("Enter the second number: ");
    read_input(input, sizeof(input));
    num2 = atoi(input);

    // 연산 수행
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                print_string("Error: Division by zero\n");
                return;
            }
            result = num1 / num2;
            break;
        default:
            print_string("Error: Invalid operator\n");
            return;
    }

    // 결과 출력
    print_string("Result: ");
    itoa(result, input);
    print_string(input);
    print_string("\n");

    while (1);
}

// 문자열을 정수로 변환
int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str) {
        result = result * 10 + (*str++ - '0');
    }
    return sign * result;
}

// 정수를 문자열로 변환
void itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    if (is_negative) {
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str);
}

// 문자열을 뒤집기
void reverse(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}
