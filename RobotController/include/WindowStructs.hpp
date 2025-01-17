#pragma once
#include "include/Skeleton/Skeleton.hpp"

namespace Madeline
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct VkObjects
	{
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkDevice device;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		QueueFamilyIndices queueIndices;
	};
	
	
	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> format;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct WinObjects
	{
		GLFWwindow* window;
		VkRenderPass renderPass;
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
		VkSurfaceKHR surface;
	};
}