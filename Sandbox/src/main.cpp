#include <Shushao.h>

using namespace se;

class Game : public Application {

    bool perspectiveTest = false;

    void Configure() {
        DEBUG_INFO("In Configuration");
    }

    void Awake() {
        DEBUG_INFO("Application is Awake");
    }

    void GetInput() override {
    }
};

se::Application* se::CreateApplication() {
    return new Game();
}
