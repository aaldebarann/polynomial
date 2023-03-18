#include "Tree.h"

int Tree::comparison(string one, string tow) {
    const char* s = &one[0];
    const char* f = &tow[0];

    if (strcmp(s, f) == 0) {
        return 0;
    }
    if (strcmp(s, f) > 0) {//str1 áîëüøå, ÷åì str2
        return 1;
    }
    if (strcmp(s, f) < 0) { //str1 ìåíüøå, ÷åì str2
        return -1;
    }
}



void Tree::insert(Node Data, nodeptr& p)
{
    if (p == NULL)
    {
        p = new Obj;
        p->DataCase = Data;
        p->left = NULL;
        p->right = NULL;
        p->height = 0;
    }
    else
    {
        if (comparison(Data.name,p->DataCase.name) == -1)
        {
            insert(Data, p->left);
            if ((bsheight(p->left) - bsheight(p->right)) == 2)
            {
                if (comparison(Data.name,p->left->DataCase.name) == -1)
                {
                    p = srl(p);
                }
                else
                {
                    p = drl(p);
                }
            }
        }
        else if (comparison(Data.name, p->DataCase.name) == 1)
        {
            insert(Data, p->right);
            if ((bsheight(p->right) - bsheight(p->left)) == 2)
            {
                if (comparison(Data.name, p->DataCase.name) == 1)
                {
                    p = srr(p);
                }
                else
                {
                    p = drr(p);
                }
            }
        }
        else
        {
            cout << "Element Exists" << endl;
        }
    }
    int m, n, d;
    m = bsheight(p->left);
    n = bsheight(p->right);
    d = max(m, n);
    p->height = d + 1;
}
Polynome Tree::find(string x, nodeptr& p)
{
    if (p == NULL)
    {
        cout << "Sorry! element not found" << endl;
        // âûçîâ îêíà ñ òåêñòîì "ýëåìåíò íå íàéäåò"
        return Polynome("0");
    }
    else
    {
        if (comparison(x, p->DataCase.name) == -1)
        {
            return(find(x, p->left));
        }
        else
        {
            if (comparison(x, p->DataCase.name) == 1)
            {
                return(find(x, p->right));
            }
            else
            {
                cout << "Element found!" << endl;
                // âûçîâ îêíà ñ òåêñòîì "ýëåìåíò íàéäåò"
                return p->DataCase.data;
            }
        }
    }

}
void Tree::copy(nodeptr& p, nodeptr& p1)
{
    clear(p1);
    p1 = nodecopy(p);
}
void Tree::clear(nodeptr& p)
{
    nodeptr d;
    if (p != NULL)
    {
        clear(p->left);
        clear(p->right);
        d = p;
        free(d);
        p = NULL;
    }
}
nodeptr Tree::nodecopy(nodeptr& p)
{
    nodeptr temp;
    if (p == NULL)
    {
        return p;
    }
    else
    {
        temp = new Obj;
        temp->DataCase.data = p->DataCase.data;
        temp->left = nodecopy(p->left);
        temp->right = nodecopy(p->right);
        return temp;
    }
}

void Tree::del(string x, nodeptr& p)
{
    nodeptr d;
    if (p == NULL)
    {
        cout << "Sorry! element not found" << endl;
        // âûçîâ îêíà ñ òåêñòîì "ýëåìåíò íå íàéäåò"
    }
    else if (comparison(x, p->DataCase.name) == -1)
    {
        del(x, p->left);
    }
    else if (comparison(x, p->DataCase.name) == 1)
    {
        del(x, p->right);
    }
    else if ((p->left == NULL) && (p->right == NULL))
    {
        d = p;
        free(d);
        p = NULL;
        cout << "Element deleted successfully" << endl;
    }
    else if (p->left == NULL)
    {
        d = p;
        free(d);
        p = p->right;
        cout << "Element deleted successfully" << endl;
    }
    else if (p->right == NULL)
    {
        d = p;
        p = p->left;
        free(d);
        cout << "Element deleted successfully" << endl;
    }
    else
    {
        p->DataCase.data = deletemin(p->right);
    }
}

Polynome Tree::deletemin(nodeptr& p)
{
    Polynome c;
    cout << "inside deltemin" << endl;
    if (p->left == NULL)
    {
        c = p->DataCase.data;
        p = p->right;
        return c;
    }
    else
    {
        c = deletemin(p->left);
        return c;
    }
}
void Tree::preorder(nodeptr p)
{
    if (p != NULL)
    {
        p->DataCase.data.print();
        preorder(p->left);
        preorder(p->right);
    }
}
void Tree::inorder(nodeptr p)
{
    if (p != NULL)
    {
        inorder(p->left);
        cout << p->DataCase.name << endl;
        p->DataCase.data.print();
        cout << endl;
        inorder(p->right);
    }
}
void Tree::postorder(nodeptr p)
{
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        p->DataCase.data.print();
    }
}

int Tree::max(int val1, int val2)
{
    return ((val1 > val2) ? val1 : val2); // небольшое пояснение ((?:a) соответствует целевой последовательности "a", но "(?:a)\1" является недопустимым, так как группа записи 1 отсутствует.) это из ML ну или
    // простыми словами если val1 > val2 то возвращаем val1 иначе val2
}
int Tree::bsheight(nodeptr p)
{
    int t;
    if (p == NULL)
    {
        return -1;
    }
    else
    {
        t = p->height;
        return t;
    }
}

nodeptr Tree::srl(nodeptr& p1)
{
    nodeptr p2;
    p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;
    p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
    p2->height = max(bsheight(p2->left), p1->height) + 1;
    return p2;
}
nodeptr Tree::srr(nodeptr& p1)
{
    nodeptr p2;
    p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;
    p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
    p2->height = max(p1->height, bsheight(p2->right)) + 1;
    return p2;
}
nodeptr Tree::drl(nodeptr& p1)
{
    p1->left = srr(p1->left);
    return srl(p1);
}
nodeptr Tree::drr(nodeptr& p1)
{
    p1->right = srl(p1->right);
    return srr(p1);
}
Tree :: ~Tree() {
    Obj* t = NULL;
    this->clear(t);
}