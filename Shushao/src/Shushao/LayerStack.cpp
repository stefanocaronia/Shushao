#include "sepch.h"

#include "LayerStack.h"

namespace Shushao {

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
        layer->OnAttach();
        index++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end()) {
            layers.erase(it);
            (*it)->OnDetach();
            index--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end()) {
            layers.erase(it);
            (*it)->OnDetach();
        }
    }

    void LayerStack::Update()
    {
        for (Layer* layer : layers) {
            layer->OnUpdate();
        }
    }

}