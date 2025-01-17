#include "include/Madeline/WindowManager/Devices.hpp"

namespace Madeline
{
	Devices::Devices(std::shared_ptr<VkObjects> vulkanObjects, const std::vector<const char*> validationLayers) :
	vulkanObjects{vulkanObjects},
	validationLayers{validationLayers}
	{}

	void Devices::pickPhysicalDevice(VkSurfaceKHR surface)
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(vulkanObjects->instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			std::cerr << "failed to find GPUs with Vulkan support!";
		}
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(vulkanObjects->instance, &deviceCount, devices.data());

		for (auto& device : devices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			if (isDeviceSuitable(device, surface) && std::strcmp(deviceProperties.deviceName, "NVIDIA GeForce RTX 4070 Laptop GPU") == 0)
			{
				vulkanObjects->physicalDevice = device;
				break;
			}
		}

		if (vulkanObjects->physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("failed to find a suitable GPU!!!");
		}
	}

	bool Devices::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices = findQueueFamilies(device, surface);

		bool extentionsSupported = checkDeviceExtensionSupport(device);

		bool swapchainAdequateFormat = false;
		bool swapchainAdequatePresent = false;
		if (extentionsSupported)
		{
			SwapchainSupportDetails swapChainSupport = Madeline::Swapchain::querySwapchainSupport(device, surface);
			swapchainAdequateFormat = !swapChainSupport.format.empty();
			swapchainAdequatePresent = !swapChainSupport.presentModes.empty();
		}
#if !NDEBUG
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		std::cout << "Device Name: " << deviceProperties.deviceName
			<< "\nGPU checks:"
			<< "\n\tQueue Familys Supported: " << boolToString(indices.isComplete())
			<< "\n\tExtensions Supported: " << boolToString(extentionsSupported)
			<< "\n\tSwapchain Adequate Format: " << boolToString(swapchainAdequateFormat)
			<< "\n\tSwapchain Adequate Present: " << boolToString(swapchainAdequatePresent)
			<< std::endl << std::endl;
#endif
		return indices.isComplete() && extentionsSupported && swapchainAdequateFormat && swapchainAdequatePresent;
	}

	QueueFamilyIndices Devices::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}
			if (presentSupport)
			{
				indices.presentFamily = i;
			}
			if (indices.isComplete())
				break;
			i++;
		}
		return indices;
	}

	bool Devices::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	void Devices::createLogicalDevice(VkSurfaceKHR surface)
	{
		vulkanObjects->queueIndices = findQueueFamilies(vulkanObjects->physicalDevice, surface);

		float queuePriority = 1.0f;
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies =
		{
			vulkanObjects->queueIndices.graphicsFamily.value(),
			vulkanObjects->queueIndices.presentFamily.value()
		};
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(vulkanObjects->physicalDevice, &createInfo, nullptr, &vulkanObjects->device) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(vulkanObjects->device, vulkanObjects->queueIndices.graphicsFamily.value(), 0, &vulkanObjects->graphicsQueue);
		vkGetDeviceQueue(vulkanObjects->device, vulkanObjects->queueIndices.presentFamily.value(), 0, &vulkanObjects->presentQueue);
	}
}
