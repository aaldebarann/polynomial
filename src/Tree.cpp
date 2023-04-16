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

bool Tree::isEmpty() {
    if (root == nullptr) return true;
    else return false;
}

void Tree::Insert(Node Data, objptr& p)
{
    if (isEmpty()) {  
        p = new Obj;
        p->DataCase = Data;
        p->left = nullptr;
        p->right = nullptr;
        p->height = 0;
        root = p;
    
    }
    else {
        if (p == nullptr)
        {
            p = new Obj;
            p->DataCase = Data;
            p->left = nullptr;
            p->right = nullptr;
            p->height = 0;
        }
        else
        {
            if (comparison(Data.name, p->DataCase.name) == 0) {
                p->DataCase.data = Data.data;
                return;
            }
            if (comparison(Data.name, p->DataCase.name) == -1)
            {
                Insert(Data, p->left);
                if ((bsheight(p->left) - bsheight(p->right)) == 2)
                {
                    if (comparison(Data.name, p->left->DataCase.name) == -1)
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
                Insert(Data, p->right);
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
                // cout << "Element Exists" << endl;
            }
        }
        int m, n, d;
        m = bsheight(p->left);
        n = bsheight(p->right);
        d = max(m, n);
        p->height = d + 1;
    }
}


Polynome Tree::find(string x, objptr& p)
{
    if (p == nullptr)
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
                // âûçîâ îêíà ñ òåêñòîì "ýëåìåíò íàéäåò"
                return p->DataCase.data;
            }
        }
    }

}
void Tree::copy(objptr& p, objptr& p1)
{
    clear(p1);
    p1 = nodecopy(p);
}
void Tree::clear(objptr& p)
{
    objptr d;
    if (p != nullptr)
    {
        clear(p->left);
        clear(p->right);
        d = p;
        free(d);
        p = nullptr;
    }
}
objptr Tree::nodecopy(objptr& p)
{
    objptr temp;
    if (p == nullptr)
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

void Tree::Del(string x, objptr& p)
{
    objptr d;
    if (p == nullptr)
    {
        return;
        //cout << "Sorry! element not found" << endl;
        // âûçîâ îêíà ñ òåêñòîì "ýëåìåíò íå íàéäåò"
    }
    else if (comparison(x, p->DataCase.name) == -1)
    {
        Del(x, p->left);
    }
    else if (comparison(x, p->DataCase.name) == 1)
    {
        Del(x, p->right);
    }
    else if ((p->left == nullptr) && (p->right == nullptr))
    {
        d = p;
        free(d);
        p = nullptr;
        //cout << "Element deleted successfully" << endl;
    }
    else if (p->left == nullptr)
    {
        d = p;
        free(d);
        p = p->right;
        //cout << "Element deleted successfully" << endl;
    }
    else if (p->right == nullptr)
    {
        d = p;
        p = p->left;
        free(d);
        //cout << "Element deleted successfully" << endl;
    }
    else
    {
        objptr pNode = p;
        objptr pN = pNode->left, * ppR = &pNode->left;
        while (pN->right != nullptr) {
            ppR = &pN->right; pN = *ppR;
        
        }
        pNode->DataCase.data = pN->DataCase.data;
        pNode->DataCase.name = pN->DataCase.name;
        pNode = pN; *ppR = pN->left;
        delete pNode;
    }
}

Polynome Tree::deletemin(objptr& p)
{
    Polynome c;
    if (p->left == nullptr)
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
void Tree::inorder() {
    inorder(root);
}
void Tree::inorder(objptr p)
{
    if (p != nullptr)
    {
        inorder(p->left);
        cout << p->DataCase.name << endl;
        p->DataCase.data.print();
        cout << "||" << endl;
        inorder(p->right);
    }
}


int Tree::max(int val1, int val2)
{
    return ((val1 > val2) ? val1 : val2); // небольшое пояснение ((?:a) соответствует целевой последовательности "a", но "(?:a)\1" является недопустимым, так как группа записи 1 отсутствует.) это из ML ну или
    // простыми словами если val1 > val2 то возвращаем val1 иначе val2
}
int Tree::bsheight(objptr p)
{
    int t;
    if (p == nullptr)
    {
        return -1;
    }
    else
    {
        t = p->height;
        return t;
    }
}

objptr Tree::srl(objptr& p1)
{
    objptr p2;
    p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;
    p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
    p2->height = max(bsheight(p2->left), p1->height) + 1;
    return p2;
}
objptr Tree::srr(objptr& p1)
{
    objptr p2;
    p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;
    p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
    p2->height = max(p1->height, bsheight(p2->right)) + 1;
    return p2;
}
objptr Tree::drl(objptr& p1)
{
    p1->left = srr(p1->left);
    return srl(p1);
}
objptr Tree::drr(objptr& p1)
{
    p1->right = srl(p1->right);
    return srr(p1);
}
Tree :: ~Tree() {
    Obj* t = nullptr;
    root = nullptr;
    this->clear(t);
}
string Tree::Print_() {
    return "Not implemented yet";
}
