#include "sepch.h"

#include "RawImageUI.h"
#include "Shushao/RawImage.h"
#include "Shushao/Transform.h"

namespace se {
	namespace ui {

		void RawImageUI::Awake() {
			transform->isRectTransform = true;
			AddComponent<se::RawImage>();
		}

	}  // namespace ui
}  // namespace se
