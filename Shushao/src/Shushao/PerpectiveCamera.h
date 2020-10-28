#pragma once

#include "Camera.h"

namespace Shushao {

    class PerpectiveCamera : public Camera
    {
    public:
        inline float GetFieldOfView() const { return fieldOfView; }
        void setFieldOfView(float _fieldOfView) { fieldOfView = _fieldOfView; UpdateProjectionMatrix(); Invalidate(); }

        virtual void UpdateProjectionMatrix() override;
        //virtual void UpdateViewMatrix() override;

        inline void Print()
        {
            {
                Logger::setColor(ConsoleColor::CYAN);
                std::cout << "Perspective Camera " << name << std::endl;
                Camera::Print();
                std::cout << "  - " << "fieldOfView: " << fieldOfView << std::endl;
                Logger::setColor(ConsoleColor::LIGHTGREY);
            }
        }

    private:
        float fieldOfView = 45.0f;

    };

}

