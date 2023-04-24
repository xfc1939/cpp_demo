#ifndef __ANY_CLASS_H__
#define __ANY_CLASS_H__

#include <memory>
#include <typeindex>
#include "Log.h"

struct Any {
    Any(void): m_tpIndex(std::type_index(typeid(void))) {}
    Any(Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex){}
    Any(Any && that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex){}
    
    template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type> 
    Any(U && value) : m_ptr(new Drived<typename std::decay<U>::type>(std::forward<U>(value)))
    , m_tpIndex(std::type_index(typeid(typename std::decay<U>::type))){}

    bool isNull() {return !m_ptr;}

    template<class U> 
    bool is() const 
    {return m_tpIndex == std::type_index(typeid(U));}

    template<class U> 
    U& anyCast() {
        if(!is<U>()) {
            ///
           throw bad_cast();
        }
        auto drived = dynamic_cast<Drived<U>*>(m_ptr.get());
        return drived->m_value;
    }

    Any &operator=(const Any& a) {
        if(m_ptr == a.m_ptr) {
            return *this;
        }
        m_ptr = a.Clone();
        m_tpIndex = a.m_tpIndex;
        return *this;
    }

private:
    struct Base;
    typedef std::unique_ptr<Base> BasePtr;
    struct Base {
        virtual ~Base() = default;
        virtual BasePtr Clone() const = 0;
    };
    template <typename T>
    struct Drived : Base{
        template<typename U>
        Drived(U && value) : m_value(std::forward<U>(value)){}
        BasePtr Clone() const {
            return BasePtr(new Drived<T>(m_value));
        }
        T m_value;
    };
    BasePtr Clone() const{
        if(m_ptr) {
            return m_ptr->Clone();
        }
        return nullptr;
    }
private:
    BasePtr m_ptr;
    std::type_index m_tpIndex;
    
};

void Any_Test()
{
    Any a;
    LOG_DEBUG() << a.isNull();
    a = std::string("hello");
    LOG_DEBUG() << a.anyCast<std::string>();
}

#endif