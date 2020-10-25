#include "sepch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Shushao {

	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;

}