#include "C:/Users/ander/source/repos/Madeline/include/Madeline/WindowManager/WindowManager.hpp"

namespace Madeline
{
	void WindowManager::initalize()
	{
		initalizeGLFW();
		createVulkanInstance();

		vkDebugMessenger.setupDebugMessenger();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		GLFWwindow* compatabilityWindow;
		compatabilityWindow = glfwCreateWindow(200, 200, "Compatability Window", nullptr, nullptr);
		if (!compatabilityWindow)
		{
			throw std::runtime_error("Failed to open window to determine device compatability");
			exit(1);
		}
		VkSurfaceKHR compatabilitySurface;
		auto result = glfwCreateWindowSurface(vulkanObjects->instance, compatabilityWindow, nullptr, &compatabilitySurface);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create surface for compatabilty window");
			exit(1);
		}

		devices.pickPhysicalDevice(compatabilitySurface);
		devices.createLogicalDevice(compatabilitySurface);

		vkDestroySurfaceKHR(vulkanObjects->instance, compatabilitySurface, nullptr);
		glfwDestroyWindow(compatabilityWindow);
	}

	void WindowManager::cleanup()
	{
		vkDeviceWaitIdle(vulkanObjects->device);
		if (windowStack.size() > 0)
		{
			throw std::runtime_error("Tried to cleanup window manager without cleaning up windows");
			exit(1);
		}
		if (enableValidationLayers)
			vkDebugMessenger.DestroyDebugUtilsMessengerEXT(vulkanObjects->instance, vulkanObjects->debugMessenger, nullptr);

		vkDestroyDevice(vulkanObjects->device, nullptr);
		vkDestroyInstance(vulkanObjects->instance, nullptr);
		glfwTerminate();
	}
	
	void WindowManager::addWindow(Madeline::WindowConfig& Config)
	{
		windowStack.push_back(Window{Config, vulkanObjects});
		windowStack.back().initalize();
	}
	
	void WindowManager::allMainLoops()
	{
		applyFunctionToAllWindows(&Window::drawFrame);
		applyFunctionToAllWindows(&Window::mainLoop);
	}
	
	bool WindowManager::areActiveWindows()
	{
		return !windowStack.empty();
	}
	
	void WindowManager::initalizeGLFW()
	{
		if ( !glfwInit() )
		{
			fprintf( stderr, "Failed to initalize GLFW\n" );
			exit( EXIT_FAILURE );
		}
	}
	
	void WindowManager::checkWindowsForCloseRequest()
	{
		auto toBeDeletedStartItorator = std::stable_partition(windowStack.begin(), windowStack.end(), [](Window window){return !window.shouldWindowClose();});
		if (toBeDeletedStartItorator != windowStack.end())
		{
			std::for_each(toBeDeletedStartItorator, windowStack.end(), [](Window window) {window.cleanupWindow(); });
			windowStack.erase(toBeDeletedStartItorator, windowStack.end());
		}
	}
	
	void WindowManager::createVulkanInstance()
	{
		if (enableValidationLayers && !checkValidationLayerSupport())
		{
			throw std::runtime_error("validation layers requested byt not available!");
		}
		
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Abigail";
		appInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
		appInfo.pEngineName = "Madeline Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();

		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();

			vkDebugMessenger.populateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;

			createInfo.pNext = nullptr;
		}

		if (vkCreateInstance(&createInfo, nullptr, &vulkanObjects->instance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}
	
	bool WindowManager::checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
			{
				return false;
			}
		}
		return true;
	}
	
	std::vector<const char*> WindowManager::getRequiredExtensions()
	{
		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
		
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
		
		if (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}
	
	void WindowManager::applyFunctionToAllWindows(pWindowMemberFunction func)
	{
		for (auto& window : windowStack)
		{
			(window.*func)();
		}
	}
}