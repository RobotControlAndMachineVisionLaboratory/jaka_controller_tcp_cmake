#include "robot_client_tcp.h"

RobotClient::RobotClient()
{}

RobotClient::RobotClient(std::string address) {
    std::cout << "construction Function of Class RobotClient!" << std::endl;
    std::cout << "Connecting to IP address : " << address << std::endl;
    const char *address_ptr = address.c_str();
    //创建socketrqt
    if ((socketrqt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "create socket error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
        exit(0);
    }

    memset(&servaddr_rqt, 0, sizeof(servaddr_rqt));
    servaddr_rqt.sin_family = AF_INET; //指定IP地址版本为IPV4
    servaddr_rqt.sin_port = htons(10001);//设置端口

    if (inet_pton(AF_INET, address_ptr, &servaddr_rqt.sin_addr) <= 0) {  //IP地址转换函数
        std::cout << "inet_pton error for " << address_ptr;
    }

    if (connect(socketrqt, (struct sockaddr *) &servaddr_rqt, sizeof(servaddr_rqt)) < 0) {
        std::cout << "connect error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
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
    close(socketrqt);
	std::cout<<"Class RobotClient Unconstructed!"<<std::endl;
}


void RobotClient::SetAout(const int &type, const int &aoutid, const float &value) {
    std::cout << "RobotClient::SetAout Started!" << std::endl;
    //SetAout
    string_tmp = "{\"cmdName\":\"set_analog_output\",\"type\":" + std::to_string(type) + ",\"index\":" +
                 std::to_string(aoutid) + ",\"value\":" + std::to_string(value) + "}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::MoveJ(const std::vector<float> &joint_vector, const float &velocity) {
    std::cout << "RobotClient::MoveJ Started!" << std::endl;

    string_tmp = "{\"cmdName\":\"joint_move\",\"jointPosition\":[" + std::to_string(joint_vector[0]) + "," +
                 std::to_string(joint_vector[1]) + "," + std::to_string(joint_vector[2]) + "," +
                 std::to_string(joint_vector[3]) + "," + std::to_string(joint_vector[4]) + "," +
                 std::to_string(joint_vector[5]) + "]" + ",\"speed\":" + std::to_string(velocity) + ",\"relFlag\":0}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
//    std::cout << "Reveived: " << buf << std::endl;

    string_tmp = "{\"cmdName\":\"wait_complete\"}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
//    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::MoveE(const std::vector<float> &cart_vector, const float &velocity) {
    std::cout << "RobotClient::MoveE Started!" << std::endl;

    string_tmp = "{\"cmdName\":\"moveL\",\"cartPosition\":[" + std::to_string(cart_vector[0]) + "," +
                 std::to_string(cart_vector[1]) + "," + std::to_string(cart_vector[2]) + "," +
                 std::to_string(cart_vector[3]) + "," + std::to_string(cart_vector[4]) + "," +
                 std::to_string(cart_vector[5]) + "]" + ",\"speed\":" + std::to_string(velocity) + ",\"relFlag\":0}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;

    string_tmp = "{\"cmdName\":\"wait_complete\"}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::SetRate(const float &rate_value) {
    std::cout << "RobotClient::SetRate Started!" << std::endl;

    //SetRate
    string_tmp = "{\"cmdName\":\"rapid_rate\",\"rate_value\":" + std::to_string(rate_value) + "}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::JogStop(const int &jogcoord, const int &axis){
    std::cout << "RobotClient::JogStop Started!" << std::endl;

    string_tmp = "{\"cmdName\":\"set_tool_id\",\"tool_id\":0}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;

    string_tmp = "{\"cmdName\":\"jog\",\"jog_mode\":0,\"coord_map\":" + std::to_string(jogcoord) + ",\"jnum\":" +
                 std::to_string(axis) + "}";
    std::cout << string_tmp << std::endl;
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::Jog(const int &jogmode, const int &jogcoord, const int &axis, const float &speed, const float &coord) {
    std::cout << "RobotClient::Jog Started!" << std::endl;

    string_tmp = "{\"cmdName\":\"set_tool_id\",\"tool_id\":0}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;

    string_tmp = "{\"cmdName\":\"jog\",\"jog_mode\":2,\"coord_map\":" + std::to_string(jogcoord) + ",\"jnum\":" +
                 std::to_string(axis) + ",\"jogvel\":" + std::to_string(speed) + ",\"poscmd\":" + std::to_string(coord) + "}";
    std::cout << string_tmp << std::endl;
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;

    string_tmp = "{\"cmdName\":\"wait_complete\"}";
    cmd_ptr = string_tmp.c_str();
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::GetRobotPose(std::vector<float>&joint, std::vector<float>&cart) {
    std::cout << "RobotClient::GetRobotPose Started!" << std::endl;
    float Arr[9], Arr2[9];
    //get data
    cmd_ptr = "{\"cmdName\":\"get_data\"}";
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';

    if(reader.parse(buf,root)) {
        int size = root["joint_actual_position"].size();
        for (Json::Value::ArrayIndex i = 0; i < size; ++i) {
            Arr[(int) i] = root["joint_actual_position"][i].asFloat();
        }
        size = root["actual_position"].size();
        for (Json::Value::ArrayIndex i = 0; i < size; ++i) {
            Arr2[(int) i] = root["actual_position"][i].asFloat();
        }
    }

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

void RobotClient::Shutdown() {
    std::cout << "RobotClient::Shutdown Started!" << std::endl;

    cmd_ptr = "{\"cmdName\":\"shutdown\"}";
    std::cout << "Send command to server:" << cmd_ptr << std::endl;
    if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
        std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
    }
    int rec_len = recv(socketrqt, buf, MAXLINE, 0);
    buf[rec_len] = '\0';
    std::cout << "Reveived: " << buf << std::endl;
}