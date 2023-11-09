#pragma once

#include <iostream>
#include <slot_map.h>
#include <string>
#include "GLHandle.h"

class GraphicsResourceManager
{
public:
    template<typename T, typename... Args>
    static GLHandle<T> ConstructObject(Args&&... args)
    {
        auto name = std::string(typeid(T).name());
        if (objectDirectory.find(name) == objectDirectory.end())
        {
            objectDirectory.insert(std::make_pair(name, new dod::slot_map<T>()));
            std::cout << "Made new slotmap for Type: " << name << std::endl;
        }

        dod::slot_map<T>* slotmap = static_cast<dod::slot_map<T>*>(objectDirectory.at(name));
        return GLHandle(slotmap->emplace(std::forward<Args>(args)...));
    }

    template<typename T>
    static GLHandle<T> AddObject(T object)
    {
        auto name = std::string(typeid(T).name());
        if (objectDirectory.find(name) == objectDirectory.end())
        {
            objectDirectory.insert(name, new dod::slot_map<T>());
        }
        dod::slot_map<T>* slotmap = objectDirectory.find(name);
        return slotmap->emplace(std::move(object));
    }

    template<typename T>
    static T* ResolveKey(const dod::slot_map_key64<T>& key)
    {
        auto name = std::string(typeid(T).name());
        if (objectDirectory.find(name) == objectDirectory.end()) return nullptr;
        dod::slot_map<T>* slotmap = static_cast<dod::slot_map<T>*>(objectDirectory.at(name));
        T* obj = slotmap->get(key);
        return obj;
    }

    template<typename T>
    static void DeleteObject(const dod::slot_map_key64<T> key)
    {
        auto name = std::string(typeid(T).name());
        if (objectDirectory.find(name) == objectDirectory.end()) return nullptr;
        dod::slot_map<T>* slotmap = objectDirectory.find(name);
        slotmap->erase(key);
    }

    inline static std::unordered_map<std::string, void*> objectDirectory = {};
};

