#pragma once
#include "include/Skeleton/Skeleton.hpp"
#include "include/Madeline/WindowManager/WindowStructs.hpp"

namespace Madeline
{
	class Swapchain
	{
	public:
		Swapchain(std::shared_ptr<VkObjects> vulkanObjects, std::shared_ptr<WinObjects> windowObjects);
		Swapchain();
		void createSwapchain();
		void createImageViews();
		void createFramebuffers();
		void cleanupSwapChain();
		void recreateSwapChain();
		VkFormat getSwapchainImageFormat() {return swapChainImageFormat;}
		VkExtent2D getSwapchainExtent() {return swapChainExtent;}
		VkSwapchainKHR& getVulkanSwapchain() {return swapchain;}
		static SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface);
		std::vector<VkFramebuffer>& getFramebufferVector() {return swapChainFramebuffers;}

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		
		std::vector<VkFramebuffer> swapChainFramebuffers;
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		VkSwapchainKHR swapchain;

		std::shared_ptr<VkObjects> vulkanObjects;
		std::shared_ptr<WinObjects> windowObjects;
	};
}


