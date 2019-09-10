//C++
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

//Customed
#include "robot_client_tcp.h"

int main(int argc, char **argv)
{
	RobotClient robotclient("192.168.1.106");

	std::vector<float> pose;
	pose={0,90,0,90,180,0};
	float vel=50;
	robotclient.MovJ(pose,vel);

	robotclient.SetAout(2,0,256);
	robotclient.SetAout(2,2,255);
	robotclient.SetAout(2,1,0);
	robotclient.SetAout(2,0,2304);

	std::vector<float> joint,cart;
	while(1)
	{
		robotclient.GetRobotPose(joint,cart);
		std::cout<<"joint = ";
		for(int i=0;i<6;i++)
		{
			std::cout<<joint[i]<<" ";
		}
		std::cout<<std::endl;
		std::cout<<"cart = ";
		for(int i=0;i<6;i++)
		{
			std::cout<<cart[i]<<" ";
		}
		std::cout<<std::endl;
	}

	std::cout<<"ready to -- SetRate";
	getchar();
	float rapid_ratio=0.6;
	robotclient.SetRate(rapid_ratio);

	return 0;
}