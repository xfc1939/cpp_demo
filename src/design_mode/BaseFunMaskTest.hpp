#ifndef __BASE_FUN_MASK_TEST_H__
#define __BASE_FUN_MASK_TEST_H__
#include "Log.h"
class A {
public:
    A(){
        LOG_DEBUG();
    }
    A(int a, int b){
        LOG_DEBUG();
    }
public:
    void test(int a){

    }
};

class B : public A {
public:
    using A::test;
    void test(){

    }
};
#endif