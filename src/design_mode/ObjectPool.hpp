#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include<string>
#include<functional>
#include<memory>
#include<map>

#include "Log.h"

const int MaxObjectNum = 10;

template<typename T>
class ObjectPool
{
public:
    template<typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
    template<typename... Args>
    void Init(size_t num, Args&&... args)
    {
        auto constructName = typeid(Constructor<Args...>).name();
        LOG_DEBUG() << "name" << constructName << num;
        for(size_t i = 0; i < num; ++i) {
            m_object_map.emplace(std::move(constructName), std::shared_ptr<T>(new T(std::forward<Args>(args)...),
            [this, constructName](T *p){
                m_object_map.emplace(std::move(constructName), std::shared_ptr<T>(p));
            }));
        }
    }
    template<typename... Args>
    std::shared_ptr<T> Get()
    {
        auto constructName = typeid(Constructor<Args...>).name();
        LOG_DEBUG() << "name" << constructName;
        auto rangs = m_object_map.equal_range(constructName);
        for(auto it = rangs.first; it != rangs.second; ++it) {
            auto ptr = it->second;
            m_object_map.erase(it);
            return ptr;
        }
        return nullptr;
    }
private:
    std::multimap<std::string, std::shared_ptr<T>> m_object_map;
};

class ObjectPool_T
{
public:
    ObjectPool_T(){

    }
    ObjectPool_T(int a, int b){

    }
};
void ObjectPool_TEST()
{
    ObjectPool<ObjectPool_T> pool;
    pool.Init(2);
    LOG_DEBUG() << pool.Get().use_count();
    LOG_DEBUG() << pool.Get().use_count();
    LOG_DEBUG() << (!pool.Get());
    pool.Init(2, 3, 4);
    auto ptr = pool.Get<int,int>();
    auto ptr1 = pool.Get<int,int>();
    auto ptr2 = pool.Get<int, int>();
    LOG_DEBUG() << (!ptr2);
}

#endif