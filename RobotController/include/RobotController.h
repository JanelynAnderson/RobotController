#pragma once

//window
#include <windows.h>

//GLFW and Vulkan
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


//std
#include <iostream>
#include <limits>
#include <exception>
#include <memory>
#include <stdint.h>
#include <vector>
#include <map>
#include <optional>
#include <set>
#include <utility>
#include <algorithm>
#include <execution>
#include <fstream>
#include <functional>
