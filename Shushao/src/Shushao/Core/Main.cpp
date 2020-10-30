#include "sepch.h"

#include "Application.h"

extern Shushao::Application* Shushao::CreateApplication();

int main(int argc, char** argv) {
    auto app = Shushao::CreateApplication();
    app->Run();
    delete app;
}
