#include "CppUnitTest.h"
#include "../ConsoleApplication4/Queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QueueTests
{
    TEST_CLASS(QueueTest)
    {
    public:
        // Тест конструктора по умолчанию
        TEST_METHOD(DefaultConstructor_ShouldCreateEmptyQueue)
        {
            Queue q;
            Assert::IsTrue(q.isEmpty());
            Assert::AreEqual(static_cast<size_t>(0), q.getSize());
            Assert::AreEqual(std::string("[]"), q.toString());
        }

        // Тест конструктора со списком инициализации
        TEST_METHOD(InitializerListConstructor_ShouldCreateQueueWithElements)
        {
            Queue q = { 1, 2, 3, 4, 5 };
            Assert::IsFalse(q.isEmpty());
            Assert::AreEqual(static_cast<size_t>(5), q.getSize());
            Assert::AreEqual(1, q.peek());
            Assert::AreEqual(std::string("[1, 2, 3, 4, 5]"), q.toString());
        }

        // Тест пустого списка инициализации
        TEST_METHOD(EmptyInitializerList_ShouldCreateEmptyQueue)
        {
            Queue q = {};
            Assert::IsTrue(q.isEmpty());
            Assert::AreEqual(static_cast<size_t>(0), q.getSize());
        }

        // Тест enqueue
        TEST_METHOD(Enqueue_ShouldAddElementToEnd)
        {
            Queue q;
            q.enqueue(10);
            q.enqueue(20);
            q.enqueue(30);

            Assert::AreEqual(static_cast<size_t>(3), q.getSize());
            Assert::AreEqual(10, q.peek());
            Assert::AreEqual(std::string("[10, 20, 30]"), q.toString());
        }

        // Тест dequeue
        TEST_METHOD(Dequeue_ShouldRemoveAndReturnFirstElement)
        {
            Queue q = { 10, 20, 30 };

            int value = q.dequeue();
            Assert::AreEqual(10, value);
            Assert::AreEqual(static_cast<size_t>(2), q.getSize());
            Assert::AreEqual(20, q.peek());
            Assert::AreEqual(std::string("[20, 30]"), q.toString());
        }

        // Тест нескольких dequeue подряд
        TEST_METHOD(Dequeue_ShouldRemoveElementsInFIFOOrder)
        {
            Queue q = { 1, 2, 3, 4, 5 };

            Assert::AreEqual(1, q.dequeue());
            Assert::AreEqual(2, q.dequeue());
            Assert::AreEqual(3, q.dequeue());
            Assert::AreEqual(static_cast<size_t>(2), q.getSize());
            Assert::AreEqual(4, q.peek());
        }

        // Тест peek
        TEST_METHOD(Peek_ShouldReturnFirstElementWithoutRemoving)
        {
            Queue q = { 5, 10, 15 };

            Assert::AreEqual(5, q.peek());
            Assert::AreEqual(static_cast<size_t>(3), q.getSize());
            Assert::AreEqual(5, q.peek()); // повторный вызов возвращает то же значение
        }

        // Тест isEmpty
        TEST_METHOD(IsEmpty_ShouldReturnTrueForEmptyQueue)
        {
            Queue q;
            Assert::IsTrue(q.isEmpty());

            q.enqueue(1);
            Assert::IsFalse(q.isEmpty());

            q.dequeue();
            Assert::IsTrue(q.isEmpty());
        }

        // Тест конструктора копирования
        TEST_METHOD(CopyConstructor_ShouldCreateDeepCopy)
        {
            Queue original = { 1, 2, 3 };
            Queue copy(original);

            Assert::AreEqual(original.getSize(), copy.getSize());
            Assert::AreEqual(original.peek(), copy.peek());
            Assert::AreEqual(original.toString(), copy.toString());

            // Изменяем оригинал - копия не должна измениться
            original.dequeue();
            Assert::AreEqual(static_cast<size_t>(2), original.getSize());
            Assert::AreEqual(static_cast<size_t>(3), copy.getSize());
            Assert::AreEqual(2, original.peek());
            Assert::AreEqual(1, copy.peek());
        }

        // Тест конструктора перемещения
        TEST_METHOD(MoveConstructor_ShouldTransferOwnership)
        {
            Queue original = { 1, 2, 3 };
            std::string originalStr = original.toString();

            Queue moved(std::move(original));

            Assert::AreEqual(originalStr, moved.toString());
            Assert::IsTrue(original.isEmpty());  // оригинал должен быть пуст
            Assert::AreEqual(static_cast<size_t>(0), original.getSize());
            Assert::AreEqual(static_cast<size_t>(3), moved.getSize());
        }

        // Тест оператора присваивания копированием
        TEST_METHOD(CopyAssignment_ShouldCopyContent)
        {
            Queue original = { 10, 20, 30 };
            Queue copy;
            copy = original;

            Assert::AreEqual(original.getSize(), copy.getSize());
            Assert::AreEqual(original.peek(), copy.peek());
            Assert::AreEqual(original.toString(), copy.toString());

            // Самоприсваивание
            copy = copy;
            Assert::AreEqual(original.toString(), copy.toString());
        }

        // Тест оператора присваивания перемещением
        TEST_METHOD(MoveAssignment_ShouldTransferOwnership)
        {
            Queue original = { 1, 2, 3 };
            std::string originalStr = original.toString();
            Queue moved;

            moved = std::move(original);

            Assert::AreEqual(originalStr, moved.toString());
            Assert::IsTrue(original.isEmpty());
            Assert::AreEqual(static_cast<size_t>(3), moved.getSize());
        }

        // Тест оператора равенства
        TEST_METHOD(EqualityOperator_ShouldCompareQueues)
        {
            Queue q1 = { 1, 2, 3 };
            Queue q2 = { 1, 2, 3 };
            Queue q3 = { 1, 2, 4 };
            Queue q4 = { 1, 2, 3, 4 };

            Assert::IsTrue(q1 == q2);
            Assert::IsFalse(q1 == q3);
            Assert::IsFalse(q1 == q4);
            Assert::IsTrue(q1 != q3);
        }

        // Тест toString
        TEST_METHOD(ToString_ShouldReturnCorrectStringRepresentation)
        {
            Queue q1 = { 1, 2, 3 };
            Assert::AreEqual(std::string("[1, 2, 3]"), q1.toString());

            Queue q2 = { 42 };
            Assert::AreEqual(std::string("[42]"), q2.toString());

            Queue empty;
            Assert::AreEqual(std::string("[]"), empty.toString());
        }

        // Тест clear
        TEST_METHOD(Clear_ShouldRemoveAllElements)
        {
            Queue q = { 1, 2, 3, 4, 5 };
            q.clear();

            Assert::IsTrue(q.isEmpty());
            Assert::AreEqual(static_cast<size_t>(0), q.getSize());
            Assert::AreEqual(std::string("[]"), q.toString());
        }

        // Тест исключения при dequeue из пустой очереди
        TEST_METHOD(Dequeue_FromEmptyQueue_ShouldThrowException)
        {
            Queue q;

            auto func = [&q]() { q.dequeue(); };
            Assert::ExpectException<std::runtime_error>(func);
        }

        // Тест исключения при peek из пустой очереди
        TEST_METHOD(Peek_FromEmptyQueue_ShouldThrowException)
        {
            Queue q;

            auto func = [&q]() { q.peek(); };
            Assert::ExpectException<std::runtime_error>(func);
        }

        // Тест больших данных
        TEST_METHOD(LargeData_ShouldWorkCorrectly)
        {
            Queue q;
            const int N = 1000;

            for (int i = 0; i < N; i++)
            {
                q.enqueue(i);
            }

            Assert::AreEqual(static_cast<size_t>(N), q.getSize());

            for (int i = 0; i < N; i++)
            {
                Assert::AreEqual(i, q.dequeue());
            }

            Assert::IsTrue(q.isEmpty());
        }

        // Тест чередования операций
        TEST_METHOD(InterleavedOperations_ShouldWorkCorrectly)
        {
            Queue q;

            q.enqueue(1);
            q.enqueue(2);
            Assert::AreEqual(1, q.dequeue());

            q.enqueue(3);
            Assert::AreEqual(2, q.peek());
            Assert::AreEqual(2, q.dequeue());

            q.enqueue(4);
            q.enqueue(5);
            Assert::AreEqual(3, q.dequeue());
            Assert::AreEqual(4, q.dequeue());
            Assert::AreEqual(5, q.dequeue());

            Assert::IsTrue(q.isEmpty());
        }
    };
}
