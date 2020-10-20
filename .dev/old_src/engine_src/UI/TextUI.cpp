#include "sepch.h"

#include "TextUI.h"
#include "Shushao/Text.h"
#include "Shushao/Transform.h"

namespace se {
    namespace ui {
        void TextUI::Awake()
        {
            transform->isRectTransform = true;
            AddComponent<se::Text>();
        }
    }  // namespace ui
}  // namespace se
