#include "Queue.h"
#include <sstream>

Queue::Queue() : head(nullptr), tail(nullptr), count(0)
{
}

Queue::Queue(const std::initializer_list<int>& list)
    : head(nullptr), tail(nullptr), count(0)
{
    for (int value : list)
    {
        enqueue(value);
    }
}

Queue::Queue(const Queue& other)
    : head(nullptr), tail(nullptr), count(0)
{
    Node* current = other.head;
    while (current != nullptr)
    {
        enqueue(current->data);
        current = current->next;
    }
}

Queue::Queue(Queue&& other) noexcept
    : head(other.head), tail(other.tail), count(other.count)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

Queue::~Queue()
{
    clear();
}

Queue& Queue::operator=(const Queue& other)
{
    if (this != &other)
    {
        Queue temp(other);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(count, temp.count);
    }
    return *this;
}

Queue& Queue::operator=(Queue&& other) noexcept
{
    if (this != &other)
    {
        clear();

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

void Queue::enqueue(int value)
{
    Node* newNode = new Node(value);

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

int Queue::dequeue()
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty! Cannot dequeue.");
    }

    Node* temp = head;
    int value = temp->data;
    head = head->next;

    if (head == nullptr)
    {
        tail = nullptr;
    }

    delete temp;
    count--;
    return value;
}

int Queue::peek() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty! Cannot peek.");
    }
    return head->data;
}

bool Queue::isEmpty() const
{
    return head == nullptr;
}

size_t Queue::getSize() const
{
    return count;
}

void Queue::clear()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

std::string Queue::toString() const
{
    std::ostringstream oss;
    oss << "[";

    Node* current = head;
    while (current != nullptr)
    {
        oss << current->data;
        if (current->next != nullptr)
        {
            oss << ", ";
        }
        current = current->next;
    }

    oss << "]";
    return oss.str();
}

bool Queue::operator==(const Queue& other) const
{
    if (count != other.count)
    {
        return false;
    }

    Node* currentThis = head;
    Node* currentOther = other.head;

    while (currentThis != nullptr && currentOther != nullptr)
    {
        if (currentThis->data != currentOther->data)
        {
            return false;
        }
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }

    return true;
}
