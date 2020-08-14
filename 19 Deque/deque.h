//
// Created by jkjan on 2020-08-14.
//

#ifndef INC_19_DEQUE_DEQUE_H
#define INC_19_DEQUE_DEQUE_H

template<typename ty>
struct node {
    ty data;
    node* prev;
    node* next;
};

template<typename ty>
class deque {
    int size;
    node<ty>* head;
    node<ty>* tail;

    node<ty>* nodeInit(ty data) {
        auto newNode = new node<ty>;
        *newNode = {data, nullptr, nullptr};
        return newNode;
    }

public:
    deque() : head(nodeInit(NULL)), tail(nodeInit(NULL)), size(0) {
        head->next = tail;
        tail->prev = head;
    }

    void push_front(ty data) {
        auto newNode = nodeInit(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        size++;
    }

    void push_back(ty data) {
        auto newNode = nodeInit(data);
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;
        size++;
    }

    void pop_front() {
        auto deletedNode = head->next;
        head->next->next->prev = head;
        head->next = head->next->next;
        delete deletedNode;
        size--;
    }

    void pop_back() {
        auto deletedNode = tail->prev;
        tail->prev->prev->next = tail;
        tail->prev = tail->prev->prev;
        delete deletedNode;
        size--;
    }

    ty front() {
        return head->next->data;
    }

    ty back() {
        return tail->prev->data;
    }

    int distFromFront(ty data) {
        int dist = 0;
        node<ty>* i = head->next;
        while (i->data != data) {
            dist++;
            i = i->next;
        }
        return dist;
    }

    int distFromBack(ty data) {
        int dist = 0;
        node<ty>* i = tail->prev;
        while (i->data != data) {
            dist++;
            i = i->prev;
        }
        return dist;
    }
};

#endif //INC_19_DEQUE_DEQUE_H
