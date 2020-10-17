#pragma once

#include "Precompiled.h"
#include "service.h"

namespace se {

class System {
public:
    static void Init();
    static void Update();
    static void Exit();
    static void Clear();
    static void ListServices();

    //static InputManager& Input;

    template <class T>
    static T& AddService() {
        T* service = new T();
        Services.push_back(service);
        return *service;
    }

    template <class T>
    static T& GetService() {
        for (Service* service : Services) {
            if (dynamic_cast<T*>(service))
                return dynamic_cast<T>(*service);
        }
        return nullptr;
    }

protected:
    static std::vector<Service*> Services;

private:
};

}  // namespace se