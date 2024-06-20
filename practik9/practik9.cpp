#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <Windows.h>

class MergeSort {
public:
    // Метод для сортировки массива слиянием
    void Sort(std::vector<int>& array) {
        if (array.size() > 1) {
            size_t mid = array.size() / 2;
            std::vector<int> left(array.begin(), array.begin() + mid);
            std::vector<int> right(array.begin() + mid, array.end());

            Sort(left);  // Рекурсивная сортировка левой части
            Sort(right); // Рекурсивная сортировка правой части

            Merge(array, left, right); // Слияние отсортированных частей
        }
    }

private:
    // Метод для слияния двух отсортированных массивов
    void Merge(std::vector<int>& array, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            array[k++] = left[i++];
        }

        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    std::vector<int> array(10);
    std::cout << "Введите 10 чисел: ";
    for (int& num : array) {
        std::cin >> num;
    }

    MergeSort sorter;

    // Создание анонимной функции для сортировки
    auto sortTask = [&sorter](std::vector<int>& arr) {
        sorter.Sort(arr);
        };

    // Создание потока для выполнения сортировки
    std::thread sortThread(sortTask, std::ref(array));

    // Ожидание завершения потока
    sortThread.join();

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
