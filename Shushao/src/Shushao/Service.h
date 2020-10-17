#pragma once

#include "Object.h"

namespace se {

class Service : public Object {
public:
    Service();
    virtual ~Service();

    bool active;

    virtual void Init();
    virtual void Update();
    virtual void Exit();

protected:
private:
};

}  // namespace se
