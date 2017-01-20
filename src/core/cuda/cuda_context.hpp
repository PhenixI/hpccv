#pragma once

#include "driver_types.h"
#include "hcvcontext.hpp"
#include "cuda_runtime.h"
#include "cuda_error.hpp"
#include <string>

inline std::string device_prop_string(cudaDeviceProp prop)
{
	int ordinal;
	cudaGetDevice(&ordinal);

	size_t freeMem, totalMem;
	checkCudaErrors(cudaMemGetInfo(&freeMem, &totalMem));

	double memBandwidth = (prop.memoryClockRate * 1000)*(prop.memoryBusWidth / 8 * 2) / 1.0e9;

	std::string s = detail::stringprintf()

}

//cuda_context_t
struct hcv_cuda_context:public hcv_context{

protected:
	cudaDeviceProp _props;
	int _ptx_version;
	cudaStream_t _stream;

	cudaEvent_t _timer[2];
	cudaEvent_t _event;

	template<int dummy_arg = 0>
	void init(){
		cudaFuncAttributes attr;
		checkCudaErrors(cudaFuncGetAttributes(&attr, dummy_k<0>));
		_ptx_version = attr.ptxVersion;

		int ord;
		cudaGetDevice(&ord);
		cudaGetDeviceProperties(&_props, ord);

		cudaEventCreate(&_timer[0]);
		cudaEventCreate(&_timer[1]);
		cudaEventCreate(&_event);
	}

public:
	hcv_cuda_context(bool print_prop = true, cudaStream_t stream_ = 0):hcv_context(), _stream(stream_)
	{
		init();
		if (print_prop)
		{
			printf("%s\n", device_prop_string(_props).c_str());
		}
	}

	//Disable copy constructor and assignment operator. We don't want to let the 
	//user copy only a slice

	hcv_cuda_context(const hcv_cuda_context& rContext) = delete;
	hcv_cuda_context& operator=(const hcv_cuda_context& rContext) = delete;

	virtual const cudaDeviceProp& getDevicesProps() const = 0;
	virtual int ptx_version() const = 0;

	virtual cudaStream_t stream() = 0;


	//Alloc GPU memory
	virtual void* malloc(size_t size, hcvmem_space space) = 0;
	virtual void free(void* p, hcvmem_space space) = 0;

	//cudaStreamSynchronize or cudaDeviceSynchronize for stream 0
	virtual void synchronize() = 0;

	virtual void event(void*) = 0;
	virtual void timer_begin() = 0;
	virtual void timer_end() = 0;

};