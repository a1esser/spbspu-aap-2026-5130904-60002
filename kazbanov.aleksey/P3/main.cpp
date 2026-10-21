#include <fstream>
#include <iostream>
#include <string>

const int invalid_argument = 1;
const int invalid_data = 2;
const int max_size = 100;

int main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return invalid_argument;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return invalid_argument;
  }
  const char* const first = argv[1];
  for (int i = 0; first[i] != '\0'; i++) {
    if (first[i] < '0' || first[i] > '9') {
      std::cerr << "First parameter is not a number\n";
      return invalid_argument;
    }
  }
  const int number = std::stoi(first);
  if (number < 1 || number > 2) {
    std::cerr << "First parameter out of range\n";
    return invalid_argument;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }
  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }

  int rows = 0;
  int cols = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "Not correct data\n";
    return invalid_data;
  }
  if (rows > max_size || rows < 0 || cols > max_size || cols < 0) {
    std::cerr << "Rows or cols is out of range\n";
    return invalid_data;
  }

  if (number == 1) {
    int arr[max_size][max_size]{};

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(input >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          return invalid_data;
        }
      }
    }

    const int count = rows * cols;
    int step = 1;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;

    while (step <= count) {
      for (int i = left; i <= right && step <= count; i++) {
        arr[top][i] -= step;
        step++;
      }
      top++;
      for (int i = top; i <= bottom && step <= count; i++) {
        arr[i][right] -= step;
        step++;
      }
      right--;
      for (int i = right; i >= left && step <= count; i--) {
        arr[bottom][i] -= step;
        step++;
      }
      bottom--;
      for (int i = bottom; i >= top && step <= count; i--) {
        arr[i][left] -= step;
        step++;
      }
      left++;
    }
    output << rows << " " << cols;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        output << " " << arr[i][j];
      }
    }
  }

  if (number == 2) {
    int alloc_count = 0;
    int** const arr = new int*[rows]();

    try {
      for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
        alloc_count++;
      }
    } catch (...) {
      for (int i = 0; i < alloc_count; i++) {
        delete[] arr[i];
      }
      delete[] arr;
      std::cerr << "Not correct data\n";
      return invalid_data;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(input >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          for (int i = 0; i < rows; i++) {
            delete[] arr[i];
          }
          delete[] arr;
          return invalid_data;
        }
      }
    }

    const int count = rows * cols;
    int step = 1;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;

    while (step <= count) {
      for (int i = left; i <= right && step <= count; i++) {
        arr[top][i] -= step;
        step++;
      }
      top++;
      for (int i = top; i <= bottom && step <= count; i++) {
        arr[i][right] -= step;
        step++;
      }
      right--;
      for (int i = right; i >= left && step <= count; i--) {
        arr[bottom][i] -= step;
        step++;
      }
      bottom--;
      for (int i = bottom; i >= top && step <= count; i--) {
        arr[i][left] -= step;
        step++;
      }
      left++;
    }

    output << rows << " " << cols;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        output << " " << arr[i][j];
      }
    }

    for (int i = 0; i < rows; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }

  input.close();
  output.close();
  return 0;
}
