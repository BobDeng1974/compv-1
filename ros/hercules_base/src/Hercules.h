#ifndef HERCULES_H_
#define HERCULES_H_

#include <string>

//#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "libserial/SerialStream.h"

#include "msg/MsgPipe.h"
#include "msg/MsgQueue.h"
#include "msg/Message.h"
#include "msg/DataEncoders.h"
#include "msg/DataDifferentialSpeed.h"

using namespace std;
using namespace LibSerial;

class Hercules {
public:
	enum Channel {
		ODOMETRY,
		DIFFERENTIALSPEED,
		MAX
	};

	Hercules();
	virtual ~Hercules();

	void connect(const std::string &port);
	void reconnect();

	void configureLimits(double max_speed, double max_accel);
	void controlSpeed(double speed_left, double speed_right,
			double accel_left, double accel_right);
	void reader();
	int processData(long *num);
	Message* requestData(Channel channel, double timeout);
        DataDifferentialSpeed* getDifferentialSpeed();

private:
	string mPort;
	SerialPort *mSerialPtr;
	boost::thread* mThread;
	int mLeftEncoder;
	int mRightEncoder;
	int mVoltage;
	int countLoop;
	bool mLeftDir[2], mRightDir[2];
	std::vector<DataEncoders> mEncoderData;
	boost::mutex mMutexEncoderData;
	MsgPipe mMsgPipe;
	MsgQueue<Channel,(int)MAX> mQueue;

	void enqueue(Message *msg);
	void processMsg(Message *msg);

protected:
	void sendDriveCmd(int left, int right, int dirL, int dirR);
	void sendGetBatteryCmd();
	int speedToLevel(double speed);
};

#endif /* HERCULES_H_ */
