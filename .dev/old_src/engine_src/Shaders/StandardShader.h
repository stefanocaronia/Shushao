#pragma once

#include "Shader.h"

namespace Shushao {

	class StandardShader : public Shader {

		public:
			StandardShader();

		protected:
			virtual void onAwake() override;
	};

}

