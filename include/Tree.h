#pragma once
#include "Table.h"
struct Obj
{
    Node DataCase;
    int height; // îíà æå ãëóáèíà
    Obj* right;
    Obj* left;

public:
    Obj() {
        height = 0;
        right = nullptr;
        left = nullptr;
    }
}; 
typedef struct Obj* objptr;

class Tree : public Table
{
private:
    objptr root = nullptr;
    int bsheight(objptr); // высота(глубина) до конкретного объекта (звена) в дереве
    objptr srl(objptr&);
    objptr drl(objptr&);// левый поворот
    objptr srr(objptr&);
    objptr drr(objptr&); //правый поворот
    int max(int, int); // максимальная из двух высот
    int comparison(string, string); // сравнение имен
    Polynome deletemin(objptr&);
    objptr nodecopy(objptr&);
    void copy(objptr&, objptr&);
    bool isEmpty();
public:

    Polynome find(string, objptr&); // получение полинома
    void Insert(Node, objptr&);
    void Del(string, objptr&);
    void clear(objptr&); // очищает дерево
    // три варианта принтов
    string inorder(objptr);
    string inorder();
    // реализация методов Table.h
    void Insert(Node val) override {
        Insert(val, root);
    }
    void Del(string name) override {
        Del(name, root);
    }
    int Search(string name) override {
        throw runtime_error("not implemented yet");
    }
    Polynome Take_elem(string name) override {
        return find(name, root);
    }
    void Print() {
        throw runtime_error("not implemented yet");
    }
    string Print_();
    ~Tree();



};
