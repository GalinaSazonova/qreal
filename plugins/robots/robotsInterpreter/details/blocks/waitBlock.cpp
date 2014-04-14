#include "waitBlock.h"

using namespace qReal::interpreters::robots::details::blocks;

WaitBlock::WaitBlock(details::RobotModel * const robotModel)
	: mRobotModel(robotModel)
{
	mActiveWaitingTimer.setInterval(20);
	connect(&mActiveWaitingTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

void WaitBlock::setFailedStatus()
{
	Block::setFailedStatus();
	stopActiveTimerInBlock();
}

void WaitBlock::processResponce(int reading, int targetValue)
{
	QString const sign = stringProperty("Sign");
	if (sign == QString::fromUtf8("equals") && reading == targetValue) {
		stop();
	} else if (sign == QString::fromUtf8("greater") && reading > targetValue) {
		stop();
	} else if (sign == QString::fromUtf8("less") && reading < targetValue) {
		stop();
	} else if (sign == QString::fromUtf8("not less") && reading >= targetValue) {
		stop();
	} else if (sign == QString::fromUtf8("not greater") && reading <= targetValue) {
		stop();
	}
}

void WaitBlock::stop()
{
	mActiveWaitingTimer.stop();
	emit done(mNextBlock);
}

void WaitBlock::failureSlot()
{
	mActiveWaitingTimer.stop();
	emit failure();
}

void WaitBlock::stopActiveTimerInBlock()
{
	mActiveWaitingTimer.stop();
}
