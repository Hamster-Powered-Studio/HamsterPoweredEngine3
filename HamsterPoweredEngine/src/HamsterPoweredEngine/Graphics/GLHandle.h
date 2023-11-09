#pragma once
#include <slot_map.h>

template<typename T>
class GLHandle
{
public:
    GLHandle()
    {
    }
    GLHandle(dod::slot_map_key64<T> key)
    {
        this->key = key;
    }

    bool IsValid()
    {
        return !key.invalid();
    }

    operator bool()
    {
        return IsValid();
    }

    T* Get() const;

    operator T*()
    {
        return Get();
    }

    bool operator ==(const GLHandle& other)
    {
        return this->key == other.key;
    }

    bool operator !=(const GLHandle& other)
    {
        return this->key != other.key;
    }
    
private:
    dod::slot_map_key64<T> key;
};

template <typename T>
T* GLHandle<T>::Get() const
{
    return GraphicsResourceManager::ResolveKey(key);
}