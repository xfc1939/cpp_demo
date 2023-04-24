#ifndef __OBSERVER_MODE__H_
#define __OBSERVER_MODE__H_
#include "Log.h"
#include <functional>
#include <map>
template<typename Func>
class Event
{
public:
    int connect(Func &&f)
    {
        return assgin(f);
    }
    int connect(const Func &f)
    {
        return assgin(f);
    }
    void disconnect(int observerId) {
        m_connection.erase(observerId);
    }
    template<typename... Args>
    void notify(Args&&... arg){
        for(auto &it : m_connections) {
            it.second(std::forward<Args>(arg)...);
        }
    }
private:
    template<typename F>
    int assgin(F &&f){
        int k = m_observerId++;
        m_connections.emplace(k, std::forward<F>(f));
        return k;
    }
private:
    std::map<int, Func> m_connections;
    int m_observerId{0};
};
void Event_Test()
{
    auto f = [](int a, int b) {
        LOG_DEBUG() << a << b;
    };
    Event<std::function<void(int, int)>> event;
    event.connect(f);
    event.notify(4,4);
}

#endif