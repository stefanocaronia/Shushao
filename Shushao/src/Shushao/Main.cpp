
#include "Precompiled.h"

#include "GameData.h"
#include "Application.h"

extern se::Application* se::CreateApplication();

int main(int argc, char** argv) {
    auto app = se::CreateApplication();
    app->Initialize();
    app->Run();
    delete app;
}
