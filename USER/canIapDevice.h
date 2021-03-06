#ifndef CAN_IAP_DEVICE_H
#define CAN_IAP_DEVICE_H
#include "device.h"
#include "CCan.h"
#include "Timer.h"

class CCanIapDevice
	:public CDevice<uint8_t>
{
	public:
		CCanIapDevice(CCanRouter& canBaseRouter,
									uint32_t txNodeId, 
									uint8_t txNodeIde, 
									uint32_t rxNodeId, 
									uint8_t rxNodeIde);	
		virtual uint32_t open();
		virtual uint32_t close();
	
		virtual uint32_t write(const uint8_t*, uint32_t);
		virtual uint32_t read(uint8_t*, uint32_t);
	
		virtual uint32_t data_in_write_buf();
		virtual uint32_t freesize_in_write_buf();
		virtual uint32_t data_in_read_buf();
		virtual void clear_read_buf();
		virtual bool is_data_flow_break();
	
		virtual void runTransmitter() {}
		virtual void runReceiver();
			
	private:
		CCanRouter& canBaseRouter_;
		ringque<uint8_t> rxBufQue_;
		CCanRxMailbox rxMailbox_;
		uint32_t txNodeId_;
		uint8_t txNodeIde_;
		Timer data_flow_break_timer_;
		uint16_t prev_elems_rx_que_;
};

extern CCanIapDevice iapDevice;

#endif
//end of file
