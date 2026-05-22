#pragma once

// @breif класс очередь
class Queue
{
private:
    struct Node
    {
        // @breif данные, хронящиеся в узле
        int data;
        // @breif указатель на следующий узел
        Node* next;
        /**
            @breif конструктор узла
            @param value значение для хронения в узле
        **/
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;      // @breif начало очереди (для извлечения)
    Node* tail;      // @breif конец очереди (для добавления)
    size_t count;    // @breif количество элементов

public:
    // @breif Конструктор
    Queue();
    /**
        @breif конструктор со списком инициализации
        @param list - список инициализации
    **/
    Queue(const std::initializer_list<int>& list);
    /**
        @breif конструктор копирования
        @param other - ссылка на копируемую очередь
    **/
    Queue(const Queue& other);
    /**
        @breif конструктор перемещения
        @param other - ссылка на перемещаемую очередь
    **/
    Queue(Queue&& other) noexcept;
    /**
        @breif деструктор
    **/
    ~Queue();
    /**
        @breif присваивание копированием
        @param other - ссылка на копируемую очередь
    **/
    Queue& operator=(const Queue& other);
    /**
        @breif присваивание перемещением
        @param other - ссылка на перемещаемую очередь
    **/
    Queue& operator=(Queue&& other) noexcept;
    /**
        @breif оператор добавить в конец очереди
        @param value - значение для добовления
    **/
    void enqueue(int value);
    /**
        @breif извлечь из начала очереди
    **/
    int dequeue();
    /**
        @breif посмотреть головной элемент
    **/
    int peek() const;
    /**
        @breif проверка на пустоту
    **/
    bool isEmpty() const;
    /**
        @breif получить размер
    **/
    size_t getSize() const;
    /**
        @breif очистить очередь
    **/
    void clear();
    /**
        @breif вывод в строку
    **/
    std::string toString() const;

    /**
        @breif Оператор сравнения
    **/
    bool operator==(const Queue& other) const;
};
