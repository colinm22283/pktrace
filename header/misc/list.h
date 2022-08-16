#pragma once

template <class T> struct listElement
{
    T data;
    listElement* next;
};

template <class T> class List
{
private:
    unsigned int length;
    listElement<T>* first;

public:
    List() : length(0)
    {
        first = nullptr;

        first = new listElement<T>;
    }
    ~List()
    {
        clear();
    };

    void push(T element)
    {
        listElement<T>* temp = first;
        for (unsigned int i = 0; i < length; i++) temp = temp->next;

        temp->data = element;
        temp->next =  new listElement<T>;

        length++;
    }

    T operator[](unsigned int index)
    {
        if (index >= length) throw std::out_of_range("Index out of bounds");

        listElement<T>* temp = first;

        for (unsigned int i = 0; i < index; i++) temp = temp->next;

        return temp->data;
    }

    T remove(unsigned int index)
    {
        if (index >= length) throw std::out_of_range("Index out of bounds");

        listElement<T>* prev = nullptr;
        listElement<T>* temp = first;

        for (unsigned int i = 0; i < index; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        listElement<T>* temp2 = prev->next;
        prev->next = temp->next;
        delete temp2;

        length--;

        return temp->data;
    }

    unsigned int size()
    {
        return length;
    }

    void clear()
    {
        listElement<T>* next = first;
        for (unsigned int i = 0; i < length; i++)
        {
            listElement<T>* temp = next;
            next = next->next;
            delete temp;
        }

        length = 0;
    }
};