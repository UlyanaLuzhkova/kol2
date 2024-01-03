// kol2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>
#include <cassert>

// Задача 1: На вход натуральное число n. На выход контейнер с первыми n факториалами.

// Функция для вычисления факториала числа
unsigned long long factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Факториал отрицательного числа не существует");
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Функция для создания контейнера с первыми n факториалами
std::vector<unsigned long long> generateFactorials(int n) {
    if (n < 0) {
        throw std::invalid_argument("Число элементов должно быть неотрицательным");
    }
    std::vector<unsigned long long> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(factorial(i));
    }
    return result;
}

// Задача 2: На вход – контейнер (массив) с числами. На выход контейнер, с неизменным списком элементов, но без дубликатов.

// Функция для удаления дубликатов из контейнера
template <class T>
std::vector<T> removeDuplicates(const std::vector<T>& input) {
    std::unordered_set<T> uniqueElements;
    std::vector<T> result;
    for (const auto& elem : input) {
        if (uniqueElements.insert(elem).second) {
            result.push_back(elem);
        }
    }
    return result;
}

// Задача 3: Развернуть связный список используя рекурсию.

// Определение структуры связного списка
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Функция для разворота связного списка с использованием рекурсии
ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* newHead = reverseList(head->next); // Рекурсивное разворачивание оставшейся части списка
    head->next->next = head; // Переворачиваем указатель на следующий элемент
    head->next = nullptr; // Задаем null последнему элементу, чтобы завершить список
    return newHead;
}

// Unit-тесты для проверки функций
void runUnitTests() {
    // Тесты для задачи 1
    {
        auto result = generateFactorials(5);
        assert(result.size() == 5);
        assert(result[0] == 1);
        assert(result[1] == 1);
        assert(result[2] == 2);
        assert(result[3] == 6);
        assert(result[4] == 24);

        bool exceptionThrown = false;
        try {
            generateFactorials(-1);
        }
        catch (const std::invalid_argument& e) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }

    // Тесты для задачи 2
    {
        std::vector<int> input = { 1, 2, 2, 3, 4, 4, 5 };
        auto result = removeDuplicates(input);
        assert(result.size() == 5);
        assert(std::find(result.begin(), result.end(), 2) == result.end());
        assert(std::find(result.begin(), result.end(), 4) == result.end());
    }

    // Тесты для задачи 3
    {
        ListNode* head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        head = reverseList(head);
        assert(head->val == 3);
        assert(head->next->val == 2);
        assert(head->next->next->val == 1);
    }
}

int main() {
    runUnitTests();
    std::cout << "All tests passed successfully" << std::endl;
    return 0;
}
