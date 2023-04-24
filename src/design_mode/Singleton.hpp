#ifndef __SINGLETON_H__
#define __SINGLETON_H__
class A;
template<typename T>
class Singleton
{
public:
    template<typename... Args>
    static T* instance(Args&&... args){
        if(instance_) {
            return instance_;
        }
        instance_ = new T(std::forward<Args>(args)...);
        return instance_;
    }

private:
    static T* instance_;
};

template<typename T>
T* Singleton<T>::instance_ = nullptr;

void Singlton_Test()
{
    auto a_init = Singleton<A>::instance(1,2);
    auto a = Singleton<A>::instance();
}
#endif