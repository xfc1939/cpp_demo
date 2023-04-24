#ifndef __VISTOR_MODE__H_
#define __VISTOR_MODE__H_

#include "Log.h"

template<class... Types>
struct Visitor;

template<class T, class... Types>
struct Visitor<T, Types...> : Visitor<Types...>
{
public:
    using Visitor<Types...>::visit;
    virtual void visit(const T &) = 0;
};

template<typename T>
struct Visitor<T>{
public:
    virtual void visit(const T &) = 0;
};

class A;
class B;
class Base {
public:
    typedef Visitor<A, B> myVisitor;
    virtual void accpet(myVisitor &v) = 0;
};

class A : public Base {
public:
    void accpet(myVisitor &v) override{
        v.visit(*this);
    }
    int a_{10};
};

class B : public Base {
public:
    void accpet(myVisitor &v) override{
        v.visit(*this);
    }
    int b_{12};
};

class VisitorA : public Base::myVisitor
{
public:
    void visit(const A &a) override {
        LOG_DEBUG() << "A.a_" << a.a_;
    }
    void visit(const B &b) override {
        LOG_DEBUG() << "B.b_" << b.b_;
    }  
};

void Visitor_TEST()
{
    VisitorA v;
    A a;
    B b;
    a.accpet(v);
    b.accpet(v);
}

#endif