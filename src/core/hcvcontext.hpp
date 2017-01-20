#pragma once

#include "hcvmem.hpp"
//hcv_context
struct hcv_context
{
	hcv_context() = default;

	//Disable copy constructor and assignment operator. We don't want to let the 
	//user copy only a slice

	hcv_context(const hcv_context& rContext) = delete;
	hcv_context& operator=(const hcv_context& rContext) = delete;

	//Alloc hcv memory
	virtual void* malloc(size_t size, hcvmem_space space) = 0;
	virtual void free(void* p, hcvmem_space space) = 0;

	//cudaStreamSynchronize or cudaDeviceSynchronize for stream 0
	virtual void synchronize() = 0;

	virtual void event(void*) = 0;
	virtual void timer_begin() = 0;
	virtual void timer_end() = 0;

};