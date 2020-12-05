#include "list.h"


size_t task::list::size() const{
    return x;
}

bool task::list::main(){
    if (n==this) return true;
    if (n==nullptr) return false;
    if (n->p==nullptr) return true;
    return !(n->p==this);
}

task::list::list(){
    p = nullptr, n = this;
    x = 0;
}

task::list::list(int a){
    p = nullptr, n = nullptr;
    x = a;
}

task::list::list(size_t count, const int& value){
    x = count;
    if (count>0){
        n = new list(value);
        p = n;
        for (int i = 0; i<count-1; ++i){
            n->n = new list(value);
            n->n->p = n;
            n = n->n;
        }
    } else {
        n = this;
        p = nullptr;
    }
}

task::list::~list(){
    if (main()){
        clear();
    }
}

bool task::list::empty() const{
    return size()==0;
}

void task::list::print() const{
    if (empty())
        std::cout << "empty" << std::endl;
    else {
        list* ptr = p;
        do {
            std::cout << ptr->x << ' ';
            ptr = ptr->n;
        } while (ptr!=nullptr);
        std::cout << std::endl;
    }
}

void task::list::clear(){
    x = 0;
    if (n==this) return;
    while (p!=n){
        n = n->p;
        delete n->n;
        n->n = nullptr;
    }
    delete n;
    n = this;
    p = nullptr;
    return;
}

task::list& task::list::operator=(const task::list& other){
    clear();
    x = other.x;
    if (x>0){
        p = new list(other.p->x);
        n = p;
    } else {
        p = nullptr;
        n = this;
        return *this;
    }
    list* ptr = other.p->n;
    while (ptr!=nullptr){
        n->n = new list(ptr->x);
        n->n->p = n;
        n = n->n;
        ptr = ptr->n;
    }
    return *this;
}

int& task::list::front(){
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    return p->x;
}

const int& task::list::front() const{
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    return p->x;
}

int& task::list::back(){
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    return n->x;
}

const int& task::list::back() const{
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    return n->x;
}

void task::list::push_back(const int& value){
    if (x==0){
        n = new list(value);
        p = n;
        x = 1;
    } else {
        n->n = new list(value);
        n->n->p = n;
        n = n->n;
        ++x;
    }
}

void task::list::pop_back(){
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    if (x==1){
        p = nullptr;
        delete n;
        n = this;
        x = 0;
    } else {
        n = n->p;
        delete n->n;
        n->n = nullptr;
        --x;
    }
}

void task::list::push_front(const int& value){
    if (x==0){
        p = new list(value);
        n = p;
        x = 1;
    } else {
        p->p = new list(value);
        p->p->n = p;
        p = p->p;
        ++x;
    }
}

void task::list::pop_front(){
    if (n==this) throw std::runtime_error("accessing a nonexistant element");
    if (x==1){
        p = nullptr;
        delete n;
        n = this;
        x = 0;
    } else {
        p = p->n;
        delete p->p;
        p->p = nullptr;
        --x;
    }
}

void task::list::resize(size_t count){
    while (x<count)
        push_back(0);
    while(x>count)
        pop_back();
}

void task::list::swap(list& other){
    std::swap(p,other.p);
    std::swap(n,other.n);
    std::swap(x,other.x);
}

void task::list::remove(const int& value){
    if (x==0) return;
    list* ptr = p;
    while(p!=nullptr){
        list* next = ptr->n;
        if (ptr->x==value){
            if (ptr->p!=nullptr)
                ptr->p->n = ptr->n;
            else
                p = ptr->n;
            if (ptr->n!=nullptr)
                ptr->n->p = ptr->p;
            else
                n = ptr->p;
            ptr->n = nullptr;
            delete ptr;
            --x;
            if (x==0) n = this;
        }
        ptr = next;
    }
}

void task::list::unique(){
    if (x==0) return;
    list* ptr = p;
    while (ptr->n!=nullptr){
        list* next = ptr->n;
        if (ptr->x==ptr->n->x){
            if (ptr->p!=nullptr)
                ptr->p->n = ptr->n;
            else
                p = ptr->n;
            ptr->n->p = ptr->p;
            ptr->n = nullptr;
            delete ptr;
            --x;
        }
        ptr = next;
    }
}

void task::list::divide(task::list& l, task::list& r){
    l = list(), r = list();
    list* ptr = p;
    for (int i = 0; i<x; ++i){
        if (i<x/2)
            l.push_back(ptr->x);
        else
            r.push_back(ptr->x);
        ptr = ptr->n;
    }
    return;
}

void task::list::sort(){
    if (x<2) return;
    list l, r;
    divide(l,r);
    l.sort();
    r.sort();
    clear();
    while (true){
        if (l.x+r.x==0) break;
        if (l.x==0){
            push_back(r.front());
            r.pop_front();
            continue;
        }
        if (r.x==0){
            push_back(l.front());
            l.pop_front();
            continue;
        }
        if (r.front()>l.front()){
            push_back(l.front());
            l.pop_front();
        } else {
            push_back(r.front());
            r.pop_front();
        }
    }
}

task::list::list(const task::list& other){
    x = other.x;
    if (x>0){
        p = new list(other.p->x);
        n = p;
    } else {
        p = nullptr;
        n = this;
    }
    list* ptr = other.p->n;
    while (ptr!=nullptr){
        n->n = new list(ptr->x);
        n->n->p = n;
        n = n->n;
        ptr = ptr->n;
    }
}
