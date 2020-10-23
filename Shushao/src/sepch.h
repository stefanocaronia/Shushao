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
#include <cstdint>

// fonts
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

// ImgUi
#include <imgui.h>

// windows
#ifdef SE_PLATFORM_WINDOWS
    #include <windows.h>
#endif

// spdlog
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Box2D
// #include <Box2D/Box2D.h>

// Includes
#include "Include/spimpl/spimpl.h"

// Core
#include "Shushao/Debug.h"
#include "Shushao/Logger.h"
#include "Shushao/Time.h"
#include "Shushao/Utility.h"
#include "Shushao/Core.h"
#include "Shushao/Globals.h"
