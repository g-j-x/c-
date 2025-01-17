#include<iostream>
#include<string>
#include<math.h>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<thread>
#include<atomic>
#include<mutex>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
mutex mutx;
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}
int main() {
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char yi[100] = { '1' };
	char er[100] = { '2' };
	char san[100] = { '3' };
	char zero[100] = { '0' };
	char send_buf[100];
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(9999);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "服务器连接成功！" << endl;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 30; j++) {
			if (i == 2 && j == 6) {
				cout << " 火车模拟购票系统 ";
				j += 18;
			}
			cout << '-';
		}
		cout << endl;
	}
	cout << endl;
	while (1) {
		cout << endl << endl << "请选择功能：" << endl << "1.查询余票/购票     2.查询车票      3.退票" << endl;

		cin >> send_buf;
		if (!strcmp(send_buf,yi)) {
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0); 
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;   //请输入起点终点
			}
			cin >> send_buf;             //输入起点站和终点站
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //票务信息
			}
			if (recv_buf[0] == '1' || recv_buf[0] == '2') {    //此处 12与功能无关
				continue;
			}
			cin>>send_buf;   //输入1  0购票与否
			if (strcmp(send_buf, yi) && strcmp(send_buf, zero)) {
				send_buf[0] = '0';
				send_len = send(s_server, send_buf, 100, 0);
				cout << "无效的功能编号！" << endl;
				continue;
			}
			if (!strcmp(send_buf, zero)) {
				send_buf[0] = '0';
				send_len = send(s_server, send_buf, 100, 0);
				cout << "欢迎下次使用！";
				continue;
			}
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //请输入姓名
			}
			cin >> send_buf;  //输入姓名
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl; //请输入身份证号
			}
			cin >> send_buf;//输入身份证号
			send_len = send(s_server, send_buf, 100, 0);
		}

		else if (!strcmp(send_buf,er)) {                      //选择了查询功能
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;   //请输入查询方式
			}
			cin >> send_buf;             //输入方式
			if (strcmp(send_buf, yi)&& strcmp(send_buf, er)) {
				send_buf[0] = '0';
				send_len = send(s_server, send_buf, 100, 0);
				cout << "无效的功能编号！" << endl;
				continue;
			}
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //请输入姓名/身份证号
			}
			cin >> send_buf;             //输入姓名/身份证号
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //输出信息
			}

		}
		else if (!strcmp(send_buf,san)) {
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //输入  1  2选择退票方式
			}
			cin >> send_buf;
			if (strcmp(send_buf, yi) && strcmp(send_buf, er)) {
				send_buf[0] = '0';
				send_len = send(s_server, send_buf, 100, 0);
				cout << "无效的功能编号！" << endl;
				continue;
			}
			send_len = send(s_server, send_buf, 100, 0);   //发送退票方式
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);  //请输入姓名/身份证号
			cout << recv_buf << endl;
			if (recv_len < 0) {
				break;
			}
			cin >> send_buf;             //输入姓名/身份证号
			send_len = send(s_server, send_buf, 100, 0);
			if (send_len < 0) {
				break;
			}
			recv_len = recv(s_server, recv_buf, 100, 0);
			if (recv_len < 0) {
				break;
			}
			else {
				cout << recv_buf << endl;  //输出退票信息
			}
		}
		else
			cout << "无效的功能编号！" << endl;
	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;
}