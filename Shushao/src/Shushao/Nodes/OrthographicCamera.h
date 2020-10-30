#pragma once

#include "Camera.h"

namespace Shushao {

    class OrthographicCamera : public Camera
    {
    public:
        inline float GetOrthographicSize() const { return orthographicSize; }
        void SetOrthographicSize(float _orthographicSize) { orthographicSize = _orthographicSize; UpdateProjectionMatrix(); InvalidateMatrix(); }

        virtual void UpdateProjectionMatrix() override;
        //virtual void UpdateViewMatrix() override;

        inline void Print()
        {
            Logger::setColor(ConsoleColor::CYAN);
            std::cout << "Orthographic Camera " << name << std::endl;
            Camera::Print();
            std::cout << "  - " << "orthographicSize: " << orthographicSize << std::endl;
            Logger::setColor(ConsoleColor::LIGHTGREY);
        }

    private:
        float orthographicSize = 5.0f;
    };

}

