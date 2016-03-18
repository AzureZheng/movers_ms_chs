/*------------------------------
MiniStation �ӿڿ�
by Azure Zheng 2016-1-20
-------------------------------*/


#ifndef __UIPC_LOADER_H__
#define __UIPC_LOADER_H__

typedef void(uipc_event_callback)(int chl, int type, int *buff, int len);

//����Ϸ������ʱ����Ҫִ��uipc_receiver_init�ӿڣ��������������ݵķ�������Init�ӿ���Ҫ����һ��callback�ص��ӿڣ��������������ݵ���ʱ�����ٿ��¼����տ⡱��ص���callback�ӿ�
//chl	������ǲٿ��¼������ĸ����豸�ֻ�
//type	������ǲٿ��¼����ͣ�
//typedef enum EVENT_TYPE_T{
//	����һ��Э��
//	SCREEN_INFO_TYPE   = 0x8000,
//	TOUCH_ALLUP_TYPE   = 0x8001,
//	TOUCH_EVENT_TYPE = 0x8002,
//	TOUCH_EVENT_TYPE2 = 0x8003,
//	SENSOR_EVENT_TYPE = 0x8004,
//	KEY_EVENT_TYPE = 0x8006,
//	TIME_SYNC_TYPE     = 0x8010,
//	RTP_STATUS_TYPE = 0x8011,
//
//	RAW DATA һ��Э��
//	RTP_RAW_TEST_TYPE = 0x9000,
//	RTP_RAW_COVER_TYPE = 0x9001,
//	RTP_RAW_GAME_CHANGED_TYPE = 0x9002,
//
//	KEEP_ALIVE_TYPE = 0x9999,
//}EVENT_TYPE;
//buff	������ǵ�ǰtype��Ӧ������
//len	����������ݵĳ���
//extern "C" void uipc_receiver_init(uipc_event_callback *dispatcher);


//����Ϸ�����˳���ʱ����Ҫ���øýӿ����ͷ���Դ����Ȼ����������쳣�˳���δ���ļ����øýӿ�Ҳû�й�ϵ
//extern "C" void uipc_receiver_release();


//�ṩ����Ϸ����ֱ�ӵ��ã�������ȡ��ǰ�Ƿ��вٿ��¼�����������Ϸ��������߳��е��ã�
//out_dev_id	��������� ������ǵ�ǰ���������ĸ��ֻ�
//out_type_id	��������� ������ǵ�ǰ������ʲô�¼������紥���¼��������¼����������¼�
//out_buff	��������� �¼���������
//out_buff_size	��������� ����ָ��out_buff����Ĵ�С
//extern "C" int uipc_receiver_poll_event(int *out_dev_id, int *out_type_id, int *out_buff, int out_buff_size);


//�ýӿ������ṩ����Ϸʹ�ã���Ϸ���Ը�����Ҫ��������ֻ����Ʋ෢�����ݡ���ʱ��û��������󣬵�������ȷ���ٲ�������
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
