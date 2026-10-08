#include <iostream>
#include <limits>

int main()
{
  const int input_error_code = 1;
  const int calculation_error_code = 2;
  const int max_value = std::numeric_limits< int >::max();
  const int even_divisor = 2;
  const char* const too_long_message = "too long\n";

  int prev = 0;
  bool has_prev = false;

  int increase = 0;
  bool increase_fail = false;

  int even_run = 0;
  int max_even_run = 0;
  bool even_fail = false;

  while (true) {
    int cur = 0;
    std::cin >> cur;
    if (std::cin.fail()) {
      std::cerr << "Error in input\n";
      return input_error_code;
    }
    if (cur == 0) {
      break;
    }

    if (!increase_fail && has_prev && (cur > prev)) {
      if (increase == max_value) {
        increase_fail = true;
      } else {
        ++increase;
      }
    }

    if (!even_fail) {
      if ((cur % even_divisor) == 0) {
        if (even_run == max_value) {
          even_fail = true;
        } else {
          ++even_run;
          if (even_run > max_even_run) {
            max_even_run = even_run;
          }
        }
      } else {
        even_run = 0;
      }
    }

    prev = cur;
    has_prev = true;
  }

  int result = 0;
  if (increase_fail) {
    std::cerr << too_long_message;
    result = calculation_error_code;
  } else {
    std::cout << increase << "\n";
  }

  if (even_fail) {
    std::cerr << too_long_message;
    result = calculation_error_code;
  } else {
    std::cout << max_even_run << "\n";
  }
  return result;
}
