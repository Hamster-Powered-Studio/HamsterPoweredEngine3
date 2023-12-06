#pragma once
#include <functional>
#include <iostream>
#include <ostream>
#include <slot_map.h>

template<typename ...Params>
class Delegate
{
public:
    using Callback = std::function<void(Params...)>;
    using CallbackKey = dod::slot_map_key64<Callback>;
    
    void Emit(Params... params)
    {
        std::cout << callbacks.size() << std::endl;
        for (Callback func : callbacks)
        {
            if (func) func(params...);
        }
    }
    
    CallbackKey Bind(Callback callback)
    {
        return callbacks.emplace(callback);
    }
    
    void Unbind(CallbackKey callback)
    {
        if (callback.invalid()) return;
        callbacks.erase(callback);
    }
    
    void UnbindAll()
    {
        callbacks.clear();
    }
    
private:
    dod::slot_map<Callback> callbacks;
};




