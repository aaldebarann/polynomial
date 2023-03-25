#pragma once
#include "Table.h"
struct Obj
{
    Node DataCase;
    int height; // îíà æå ãëóáèíà
    Obj* right;
    Obj* left;
};
typedef struct Obj* nodeptr;

class Tree
{
private:
    int bsheight(nodeptr); // высота(глубина) до конкретного объекта (звена) в дереве
    nodeptr srl(nodeptr&);
    nodeptr drl(nodeptr&);// левый поворот
    nodeptr srr(nodeptr&);
    nodeptr drr(nodeptr&); //правый поворот
    int max(int, int); // максимальная из двух высот
    int comparison(string, string); // сравнение имен
    Polynome deletemin(nodeptr&);
    nodeptr nodecopy(nodeptr&);
    void copy(nodeptr&, nodeptr&);
public:
    Polynome find(string, nodeptr&); // получение полинома
    void Insert(Node, nodeptr&);
    void Del(string, nodeptr&);
    void clear(nodeptr&); // очищает дерево
    // три варианта принтов
    void preorder(nodeptr);
    void inorder(nodeptr);
    void postorder(nodeptr);
    ~Tree();



};
