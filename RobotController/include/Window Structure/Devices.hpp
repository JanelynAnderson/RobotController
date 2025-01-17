#pragma once
#include "include/Skeleton/Skeleton.hpp"
#include "include/Madeline/WindowManager/WindowStructs.hpp"
#include "include/Madeline/WindowManager/Swapchain.hpp"

namespace Madeline
{
	class Devices
	{
	public:
		Devices(std::shared_ptr<VkObjects> vulkanObjects, const std::vector<const char*> validationLayers);
		void pickPhysicalDevice(VkSurfaceKHR surface);
		void createLogicalDevice(VkSurfaceKHR surface);

	private:
		bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
		std::string boolToString(bool value) { return value ? "TRUE" : "FALSE"; }

		std::shared_ptr<VkObjects> vulkanObjects;

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		const std::vector<const char*> validationLayers;

		#ifdef NDEBUG
			const bool enableValidationLayers = false;
		#else
			const bool enableValidationLayers = true;
		#endif
	};
}
