#ifndef __JAKA_ROBOT_CLIENT_TCP_H_
#define __JAKA_ROBOT_CLIENT_TCP_H_

#include <string>
#include <vector>
#include <memory>

class RobotClient
{
public:
	RobotClient(std::string address);
	RobotClient();
	~RobotClient();
	int setIP(std::string address);
	int SetRate(float rate_value);
	int SetAout(int type, int doutid, float value);
	int GetRobotPose(std::vector<float>&jnt, std::vector<float>&cart);
	int MovJ(std::vector<float> pos_vector, float velocity);
	int Shutdown();

private:
	int read_json_JointPose(const char *json_ptr, float arr[9]);
	int read_json_CartPose(const char *json_ptr, float arr[9]);
};

#endif
