#include <config.hxx>
#include <cxx/cstdio>
#include <cxx/cstdlib>
#include <cxx/cstring>
#include <fcntl.h>
#include <core.hxx>
#include <adapter.hxx>

#include <port.hxx>


#define SERIAL_LISTENER_BUFFER_SIZE 200

class SerialDaemon
{
	static SerialDaemon serial_daemon;
	adapter::Thread listener;
	adapter::Thread writer;
	SerialDaemon( const SerialDaemon &) = delete;
	void operator=(const SerialDaemon &) = delete;

	static void * ListenThreadRunner(void *)
	{
		int fd = open("/dev/console", O_RDONLY);
		if(fd < 0 ){
			std::printf("cannot open /dev/console\n");
		}
		uint8_t buffer[SERIAL_LISTENER_BUFFER_SIZE];
		bool sampling_status = true;
		uint16_t buffer_index = 0;

		vts::command::Port * port = vts::command::Port::GetInstance(vts::command::PortType::PORT_SERIAL);
		while(1)
		{
			uint8_t c = 0;

			int ret = read(fd, &c, 1);
			//std::printf("%02X ", c);
			if(ret != 0)
			{
				if(c == CONFIG_PROTOCOL_START_BYTE  || c == CONFIG_PROTOCOL_STOP_BYTE)
				{
					if(c == CONFIG_PROTOCOL_STOP_BYTE && buffer_index != 0)
					{
						//std::printf("packet reading end..\n");
						//for(int i = 0; i < buffer_index; i ++)
						//{
						//	std::printf("%02X ", buffer[i]);
						//	if(i==buffer_index-1){
						//		std::printf(" \n");
						//	}
						//}

						if(port->Write(buffer, buffer_index))
						{
							//std::printf("\nPacket write success.\n");
						}
						sampling_status = false;
						//std::printf("New packet handled.\n");
						buffer_index = 0;
					}
					else if(c == CONFIG_PROTOCOL_START_BYTE)
					{
						sampling_status = true;
						buffer_index = 0;
						std::memset(buffer, 0, SERIAL_LISTENER_BUFFER_SIZE);
						//std::printf("Sampling start..\n");
					}
				}
				else
				{
					if(sampling_status)
					{
						buffer[buffer_index++] = c;
						if(buffer_index >= SERIAL_LISTENER_BUFFER_SIZE)
						{
							sampling_status = false;
						}
					}
				}
			}
			else
			{
				//std::printf("No data read.\n");
			}
		}
	}

	static void * WriterThreadRunner(void *)
	{
		//int fd = open("/dev/console", O_WRONLY);
		uint8_t buffer[SERIAL_LISTENER_BUFFER_SIZE];

		vts::command::Port * port = vts::command::Port::GetInstance(vts::command::PortType::PORT_SERIAL);
		while(1)
		{
			uint16_t ret = port->Read(buffer, SERIAL_LISTENER_BUFFER_SIZE);
			if(ret != 0)
			{
				fwrite(buffer, 1, ret, stdout);
				//std::printf("print the output buffer...\n");
				for(int i = 0; i < ret; i ++)
				{
					std::printf("%02X", buffer[i]);
				}
				std::printf(" \n");
			}
			//sleep(10);
		}
	}

	public:
	SerialDaemon()
	{
		listener.SetStartRoutine(ListenThreadRunner);
		writer.SetStartRoutine(WriterThreadRunner);

	}

	static SerialDaemon & GetInstance()
	{
		return serial_daemon;
	}

	void Run()
	{
		int ret = listener.Run();
		std::printf("thredrunner return :%d\n",ret);
		ret = writer.Run();
		std::printf("thredrunner return :%d\n",ret);
	}


};

SerialDaemon SerialDaemon::serial_daemon;



int v_main()
{
	std::printf("Let the show begin!!!\n");
	vts::InitCommandModule();
	vts::InitEventModule();
	SerialDaemon & serial_daemon = SerialDaemon::GetInstance();
	serial_daemon.Run();


	vts::InitEngineModule();
	vts::InitAcInstance();
	while(1){
		sleep(100);
	}
	return 0;
}
