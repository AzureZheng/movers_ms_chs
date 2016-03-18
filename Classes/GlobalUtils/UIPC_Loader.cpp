#include "UIPC_Loader.h"
#ifndef _WIN32
#include <dlfcn.h>
#include <android/log.h>
#endif

//void uipc_receiver_init(uipc_event_callback *dispatcher){}


//void uipc_receiver_release(){}


//int uipc_receiver_poll_event(int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size){ return -1; }


//int uipc_receiver_upload(char *buff, int len){ return -1; }

namespace UIPC_Loader
{
	int(*uipc_receiver_upload)(char *buff, int len) = [](char *buff, int len){return -1; };
	int(*uipc_receiver_poll_event)(int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size) = [](int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size){return -1; };
	void(*uipc_receiver_release)() = [](){};
	void(*uipc_receiver_init)(uipc_event_callback *dispatcher) = [](uipc_event_callback *dispatcher){};
	bool loader_open_finished = false;

	void reload()
	{
		loader_open_finished = false;
#ifndef _WIN32
		void * libm_handle = nullptr;
		__android_log_print(ANDROID_LOG_INFO,"Azure","Handel Opening");
		libm_handle = dlopen("/system/lib/libuipc_loader.so", RTLD_NOW | RTLD_GLOBAL);
		if (!libm_handle)
		{
			__android_log_print(ANDROID_LOG_INFO,"Azure","Handel Open Failed!");
			reloadEmpty();
			return;
		}

		//uipc_receiver_upload = (int(*)(char*,int))(dlsym(libm_handle, "uipc_receiver_upload"));
		//if (dlerror() != nullptr) { reloadEmpty(); dlclose(libm_handle);__android_log_print(ANDROID_LOG_INFO,"Azure","Handel upload Failed!"); return; }

		uipc_receiver_poll_event = (int(*)(int*,int*,int*,int))dlsym(libm_handle, "uipc_receiver_poll_event");
		if (dlerror() != nullptr) { reloadEmpty(); dlclose(libm_handle);__android_log_print(ANDROID_LOG_INFO,"Azure","Handel poll Failed!"); return; }

		uipc_receiver_release = (void(*)())dlsym(libm_handle, "uipc_receiver_release");
		if (dlerror() != nullptr) { reloadEmpty(); dlclose(libm_handle);__android_log_print(ANDROID_LOG_INFO,"Azure","Handel release Failed!"); return; }

		uipc_receiver_init = (void(*)(uipc_event_callback*))dlsym(libm_handle, "uipc_receiver_init");
		if (dlerror() != nullptr) { reloadEmpty(); dlclose(libm_handle);__android_log_print(ANDROID_LOG_INFO,"Azure","Handel init Failed!"); return; }

		__android_log_print(ANDROID_LOG_INFO,"Azure","Handel Open Finished!");
		loader_open_finished = true;

		//dlclose(libm_handle);
		return;
#endif
		reloadEmpty();
	}


	void reloadEmpty()
	{
#ifndef _WIN32
		__android_log_print(ANDROID_LOG_INFO,"Azure","Handel Open Failed!");
#endif
		uipc_receiver_upload = [](char *buff, int len){return -1; };
		uipc_receiver_poll_event = [](int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size){return -1; };
		uipc_receiver_release = [](){};
		uipc_receiver_init = [](uipc_event_callback *dispatcher){};
	}
}
