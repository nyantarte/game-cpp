#pragma once
#include <memory>

template<typename T>
class CSingleton{
    std::shared_ptr<T> m_obj;

public:
    T* get(){
        if(nullptr==m_obj){
            m_obj.reset(new T());
        }
        return m_obj.get();
    }
};
