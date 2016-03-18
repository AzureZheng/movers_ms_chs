/*------------------------------
MiniStation 接口库
by Azure Zheng 2016-1-20
-------------------------------*/


#ifndef __UIPC_LOADER_H__
#define __UIPC_LOADER_H__

typedef void(uipc_event_callback)(int chl, int type, int *buff, int len);

//在游戏启动的时候，需要执行uipc_receiver_init接口，来启动接收数据的服务器。Init接口需要传入一个callback回调接口，当有完整的数据到来时，“操控事件接收库”会回调该callback接口
//chl	用来标记操控事件来自哪个从设备手机
//type	用来标记操控事件类型：
//typedef enum EVENT_TYPE_T{
//	基础一级协议
//	SCREEN_INFO_TYPE   = 0x8000,
//	TOUCH_ALLUP_TYPE   = 0x8001,
//	TOUCH_EVENT_TYPE = 0x8002,
//	TOUCH_EVENT_TYPE2 = 0x8003,
//	SENSOR_EVENT_TYPE = 0x8004,
//	KEY_EVENT_TYPE = 0x8006,
//	TIME_SYNC_TYPE     = 0x8010,
//	RTP_STATUS_TYPE = 0x8011,
//
//	RAW DATA 一级协议
//	RTP_RAW_TEST_TYPE = 0x9000,
//	RTP_RAW_COVER_TYPE = 0x9001,
//	RTP_RAW_GAME_CHANGED_TYPE = 0x9002,
//
//	KEEP_ALIVE_TYPE = 0x9999,
//}EVENT_TYPE;
//buff	用来标记当前type对应的数据
//len	用来标记数据的长度
//extern "C" void uipc_receiver_init(uipc_event_callback *dispatcher);


//在游戏主动退出的时候，需要调用该接口来释放资源。当然，如果属于异常退出，未来的及调用该接口也没有关系
//extern "C" void uipc_receiver_release();


//提供给游戏引擎直接调用，用来获取当前是否有操控事件（可以在游戏引擎的主线程中调用）
//out_dev_id	输出参数： 用来标记当前数据来自哪个手机
//out_type_id	输出参数： 用来标记当前数据是什么事件，例如触屏事件、按键事件、传感器事件
//out_buff	输出参数： 事件本身数据
//out_buff_size	输入参数： 用来指明out_buff缓存的大小
//extern "C" int uipc_receiver_poll_event(int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size);


//该接口用来提供给游戏使用，游戏可以根据需要，向各个手机控制侧发送数据。暂时还没有相关需求，等需求明确后再补充完善
//extern "C" int uipc_receiver_upload(char *buff, int len);



namespace UIPC_Loader
{
	void reload();

	void reloadEmpty();

	extern "C" int(*uipc_receiver_upload)(char *buff, int len);
	extern "C" int(*uipc_receiver_poll_event)(int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size);
	extern "C" void(*uipc_receiver_release)();
	extern "C" void(*uipc_receiver_init)(uipc_event_callback *dispatcher);
	extern "C" bool loader_open_finished;
};



#endif
