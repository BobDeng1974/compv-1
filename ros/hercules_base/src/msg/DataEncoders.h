/*
 * DataEncoders.h
 *
 *  Created on: Apr 17, 2015
 *      Author: danke
 */

#ifndef DATAENCODERS_H_
#define DATAENCODERS_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include "Message.h"
namespace bpt = boost::posix_time;
class DataEncoders : public Message {
private:
	int mLeftEncoder, mRightEncoder;
	double mLeftSpeed, mRightSpeed;
	bool mLeftDir, mRightDir;
	bpt::ptime mTimeStamp;
	double encoderToTravel(int enc);

public:
	//	DataEncoders(int left, int right);
	DataEncoders(int left, int right, bpt::ptime timeStamp);
	//        DataEncoders(DataEncoders const &);
	virtual ~DataEncoders();

	double getTravel(int encoderId);
	double getSpeed(int encoderId);
	bpt::ptime getTimeStamp();
	void setDir(bool left, bool right);
	void setOrigin(int left, int right);
	void getData(int &left, int &right);
	static DataEncoders* parse(const string &msg);

	virtual void dump();
};

#endif /* DATAENCODERS_H_ */
