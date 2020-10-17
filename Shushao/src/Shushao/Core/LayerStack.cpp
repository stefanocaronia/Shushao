#include "Precompiled.h"

#include "LayerStack.h"

namespace se {

    LayerStack::LayerStack() {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        layers.emplace(layers.begin() + index, layer);
        index++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end()) {
            layers.erase(it);
            index--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end())
            layers.erase(it);
    }

    void LayerStack::Update()
    {
        for (Layer* layer : layers) {
            layer->OnUpdate();
        }
    }

}