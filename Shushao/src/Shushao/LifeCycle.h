#pragma once

namespace Shushao {

    class LifeCycle
    {
        virtual void Awake() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    };
}