#pragma once

#include "include/Skeleton/Skeleton.hpp"
#include "include/Madeline/WindowManager/WindowStructs.hpp"
namespace Madeline
{
	class VulkanDebugMessenger
	{
	public:
		VulkanDebugMessenger(std::shared_ptr<VkObjects> vulkanObjects);

		void setupDebugMessenger();
		
		void DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks* pAllocator
		);

		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	
	private:
		VkResult CreateDebugUtilsMessengerEXT
		(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
		(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData
		);

		std::shared_ptr<VkObjects> vulkanObjects;

		#ifdef NDEBUG
			const bool enableValidationLayers = false;
		#else
			const bool enableValidationLayers = true;
		#endif
	};
}
