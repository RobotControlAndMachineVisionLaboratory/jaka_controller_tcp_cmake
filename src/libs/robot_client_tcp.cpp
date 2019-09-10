//C++
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//json
#include <json/json.h>
//Customed
#include "robot_client_tcp.h"

#define MAXLINE 4096

int socketrqt,socketrcv,rec_len; // int n;
struct sockaddr_in servaddr_rqt,servaddr_rcv;
char    buf[MAXLINE];
const char *cmd_ptr;
std::string string_tmp;



int RobotClient::read_json_JointPose(const char *json_ptr, float arr[9])
{
	Json::Reader reader;
	Json::Value root;
	if(reader.parse(json_ptr,root)) {
		int size=root["joint_actual_position"].size();
		for(Json::Value::ArrayIndex i=0;i<size;++i){
			arr[(int)i]=root["joint_actual_position"][i].asFloat();
		}
	}
}

int RobotClient::read_json_CartPose(const char *json_ptr, float arr[9])
{
	Json::Reader reader;
	Json::Value root;
	if(reader.parse(json_ptr,root)) {
		int size=root["actual_position"].size();
		for(Json::Value::ArrayIndex i=0;i<size;++i){
			arr[(int)i]=root["actual_position"][i].asFloat();
		}
	}
}

RobotClient::RobotClient()
{}

RobotClient::RobotClient(std::string address)
{
	std::cout<<"construction Function of Class RobotClient!"<<std::endl;
	std::cout<<"Connecting to IP address : "<<address<<std::endl;
	const char* address_ptr=address.c_str();
	//创建socketrqt
	if ((socketrqt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr_rqt, 0, sizeof(servaddr_rqt));
	servaddr_rqt.sin_family = AF_INET; //指定IP地址版本为IPV4
	servaddr_rqt.sin_port = htons(10001);//设置端口

	if (inet_pton(AF_INET, address_ptr, &servaddr_rqt.sin_addr) <= 0) {  //IP地址转换函数
		printf("inet_pton error for %s\n", address_ptr);
	}

	if (connect(socketrqt, (struct sockaddr *) &servaddr_rqt, sizeof(servaddr_rqt)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
	}

	std::cout << "Socketrqt connects successfully!" << std::endl;

//    //上电RobotClient
//    cmd_ptr="{\"cmdName\":\"power_on\"}";
//    std::cout<<"Send command to server:"<< cmd_ptr<<std::endl;
//    if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
//    {
//        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
//    }
//    rec_len = recv(socketrqt, buf, MAXLINE,0);
//    buf[rec_len]  = '\0';
//    printf("Received : %s \n",buf);

	//使能
//    cmd_ptr="{\"cmdName\":\"enable_robot\"}";
//    std::cout<<"Send command to server:"<< cmd_ptr<<std::endl;
//    if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
//    {
//        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
//    }
//    rec_len = recv(socketrqt, buf, MAXLINE,0);
//    buf[rec_len]  = '\0';
//    printf("Received : %s \n",buf);
}

RobotClient::~RobotClient()
{
	std::cout<<"\n\tClass RobotClient Unconstructed!"<<std::endl;
}


int RobotClient::SetAout(int type, int aoutid, float value)
{
	std::cout<<"RobotClient::SetAout Started!"<<std::endl;
	//SetAout
	string_tmp="{\"cmdName\":\"set_analog_output\",\"type\":"+std::to_string(type) + ",\"index\":"+std::to_string(aoutid)+",\"value\":"+std::to_string(value)+"}";
	cmd_ptr=string_tmp.c_str();
	if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	}
	rec_len = recv(socketrqt, buf, MAXLINE,0);
	buf[rec_len]  = '\0';
	printf("Received : %s \n",buf);
}

int RobotClient::MovJ(std::vector<float> pos_vector, float velocity)
{
	std::cout<<"RobotClient::MovJ Started!"<<std::endl;

	//MoveJ
	string_tmp="{\"cmdName\":\"joint_move\",\"jointPosition\":["+std::to_string(pos_vector[0])+","+std::to_string(pos_vector[1])+","+std::to_string(pos_vector[2])+","+std::to_string(pos_vector[3])+","+std::to_string(pos_vector[4])+","+std::to_string(pos_vector[5])+"]"+",\"speed\":"+std::to_string(velocity)+",\"relFlag\":0}";
	cmd_ptr=string_tmp.c_str();
	if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	}
	rec_len = recv(socketrqt, buf, MAXLINE,0);
	buf[rec_len]  = '\0';
	printf("Received : %s \n",buf);
}

int RobotClient::SetRate(float rate_value)
{
	std::cout<<"RobotClient::SetRate Started!"<<std::endl;

	//SetRate
	string_tmp="{\"cmdName\":\"rapid_rate\",\"rate_value\":"+std::to_string(rate_value)+"}";
	cmd_ptr=string_tmp.c_str();
	if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	}
	rec_len = recv(socketrqt, buf, MAXLINE,0);
	buf[rec_len]  = '\0';
	printf("Received : %s \n",buf);
}

int RobotClient::GetRobotPose(std::vector<float>&joint, std::vector<float>&cart)
{
	std::cout<<"RobotClient::GetRobotPose Started!"<<std::endl;
	float Arr[9],Arr2[9];
	//get data
	cmd_ptr="{\"cmdName\":\"get_data\"}";
	if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	}
	rec_len = recv(socketrqt, buf, MAXLINE,0);
	buf[rec_len]  = '\0';
	//printf("Received : %s \n",buf);
	RobotClient::read_json_JointPose(buf,Arr);
	RobotClient::read_json_CartPose(buf,Arr2);

	joint.clear();
	joint.push_back(Arr[0]);
	joint.push_back(Arr[1]);
	joint.push_back(Arr[2]);
	joint.push_back(Arr[3]);
	joint.push_back(Arr[4]);
	joint.push_back(Arr[5]);

	cart.clear();
	cart.push_back(Arr2[0]);
	cart.push_back(Arr2[1]);
	cart.push_back(Arr2[2]);
	cart.push_back(Arr2[3]);
	cart.push_back(Arr2[4]);
	cart.push_back(Arr2[5]);

}

int RobotClient::Shutdown()
{
	std::cout<<"RobotClient::Shutdown Started!"<<std::endl;

	cmd_ptr="{\"cmdName\":\"shutdown\"}";
	std::cout<<"Send command to server:"<< cmd_ptr<<std::endl;
	if( send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0)
	{
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	}
	rec_len = recv(socketrqt, buf, MAXLINE,0);
	buf[rec_len]  = '\0';
	printf("Received : %s \n",buf);

}