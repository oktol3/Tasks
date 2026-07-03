#include <iostream>
#include <vector>
#include "Queue.h"

/**
 * @brief Точка входа
 * @return 0, если код завершился успешно
 */
int main()
{
    Queue q1;
    std::cout << "1. Пустая очередь q1: " << q1.toString() << std::endl;
    std::cout << "   Пустая? " << (q1.isEmpty() ? "Да" : "Нет") << std::endl;
    std::cout << "   Размер: " << q1.getSize() << std::endl << std::endl;

    Queue q2 = { 10, 20, 30, 40, 50 };
    std::cout << "2. Очередь q2 (список инициализации): " << q2.toString() << std::endl;
    std::cout << "   Размер: " << q2.getSize() << std::endl << std::endl;

    q1.enqueue(100);
    q1.enqueue(200);
    q1.enqueue(300);
    std::cout << "   После добавления 100, 200, 300: " << q1.toString() << std::endl;
    std::cout << "   Размер: " << q1.getSize() << std::endl << std::endl;

    int value = q1.dequeue();
    std::cout << "   Извлечено: " << value << std::endl;
    std::cout << "   После извлечения: " << q1.toString() << std::endl;

    value = q1.dequeue();
    std::cout << "   Извлечено: " << value << std::endl;
    std::cout << "   После извлечения: " << q1.toString() << std::endl;
    std::cout << "   Размер: " << q1.getSize() << std::endl << std::endl;

    Queue q7;

    for (int i = 1; i <= 10; i++)
    {
        q7.enqueue(i);
    }
    std::cout << "   Очередь после добавления 1..10: " << q7.toString() << std::endl;

    std::cout << "   Извлекаем первые 5 элементов: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << q7.dequeue() << " ";
    }
    std::cout << std::endl;
    std::cout << "   Очередь после извлечения: " << q7.toString() << std::endl;
    std::cout << "   Размер: " << q7.getSize() << std::endl << std::endl;

    return 0;
}
