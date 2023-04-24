#ifndef __COMMAND_MODE_H__
#define __COMMAND_MODE_H__
#include <memory>
#include "Log.h"
template<class F, class... Args, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
void Wrap(F &&f, Args && ...args){
    return f(std::forward<Args>(args)...);
}
template<class R, class C, class... DArgs, class P, class... Args>
void Wrap(R(C::*f)(DArgs...), P &&p, Args && ...args) {
    return (*p.*f)(std::forward<Args>(args)...);
}

template<class R = void>
struct Command
{
private:
    std::function <R()> m_f;
public:
    template<class F, class... Args, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
    void Wrap(F &&f, Args && ...args){
        m_f =[&]{ return f(std::forward<Args>(args)...);};
    }

    template<class R, class C, class... DArgs, class P, class... Args>
    void Wrap(R(C::*f)(DArgs...) const, P &&p, Args && ...args) {
        m_f = [&, f]{return (*p.*f)(std::forward<Args>(args)...);};
    }

     template<class R, class C, class... DArgs, class P, class... Args>
    void Wrap(R(C::*f)(DArgs...), P &&p, Args && ...args) {
        m_f = [&, f]{return (*p.*f)(std::forward<Args>(args)...);};
    }
    R exec() {
        return m_f();
    }
};

class A
{
public:
    int test1(int a) {
        LOG_DEBUG() << a;
        return a;
    }
    int test2(int a) const {
        LOG_DEBUG() << a;
        return a;
    }
    int operator() (){
        return value_;
    }
    int value_{5};
};

void CommandMode_TEST()
{
    Command cmd;
    cmd.Wrap([](int a){LOG_DEBUG() << a;}, 1);
    cmd.exec();
    Command<int> cmd1;
    A t;
    cmd1.Wrap(t);
    LOG_DEBUG() << cmd1.exec();
    cmd1.Wrap(&A::test1, &t, 3);
    LOG_DEBUG() << cmd1.exec();
    
    cmd1.Wrap(&A::test2, &t, 2);
    LOG_DEBUG() << cmd1.exec();
}

#endif