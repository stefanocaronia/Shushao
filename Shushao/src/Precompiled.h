#pragma once

// std
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>
#include <cmath>

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// boost
#define BOOST_ALL_NO_LIB
#include <boost/predef.h>
#include <boost/coroutine2/all.hpp>
#include <boost/variant.hpp>

#if BOOST_COMP_GNUC
#include <dirent.h>
#endif

// GLM
#include <glm/glm.hpp>
#define GLM_FORCE_SWIZZLE
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/transform.hpp>

// OpenGL
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// windows
#ifdef SE_PLATFORM_WINDOWS
    #include <windows.h>
#endif

// spdlog
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Box2D
#include <Box2D/Box2D.h>

// Includes
#include "Include/spimpl/spimpl.h"

// Shushao
#include "Shushao/Core/Debug.h"
#include "Shushao/Core/Logger.h"
#include "Shushao/Core/Time.h"
#include "Shushao/Core/Utility.h"
#include "Shushao/Core/OpenGL.h"
#include "Shushao/Core/Core.h"
#include "Shushao/Core/Globals.h"
