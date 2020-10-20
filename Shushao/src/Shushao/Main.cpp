
#include "sepch.h"

#include "Application.h"

extern se::Application* se::CreateApplication();

int main(int argc, char** argv) {
    auto app = se::CreateApplication();
    app->Run();
    delete app;
}
