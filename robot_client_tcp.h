#ifndef __JAKA_ROBOT_CLIENT_TCP_H_
#define __JAKA_ROBOT_CLIENT_TCP_H_

#define MAXLINE 8192

#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>

class RobotClient {
public:
    RobotClient(std::string address);

    RobotClient();

    ~RobotClient();

    void SetRate(const float &rate_value);

    void SetAout(const int &type, const int &doutid, const float &value);

    void GetRobotPose(std::vector<float> &jnt, std::vector<float> &cart);

    void MoveJ(const std::vector<float> &joint_vector, const float &velocity);

    void MoveE(const std::vector<float> &cart_vector, const float &velocity);

    void Jog(const int &jogmode, const int &jogcoord, const int &axis, const float &speed, const float &coord);

    void JogStop(const int &jogcoord, const int &axis);

    void Shutdown();

private:
    Json::Reader reader;
    Json::Value root;
    int socketrqt, socketrcv;
    struct sockaddr_in servaddr_rqt, servaddr_rcv;
    char buf[MAXLINE];
    const char *cmd_ptr;
    std::string string_tmp;
};

#endif
