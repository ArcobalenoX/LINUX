#include "myhead.h"

int iphonex;
struct sockaddr_in phoneaddr ;
struct sockaddr_in bindaddr;
int addrsize ;


int main(int argc, char *argv[])
{
	
	if(argc != 4){
		fprintf(stderr, "usage: %s  <local_port>  <recv_ip> <recv_port>",argv[0]);
		exit(-1);
	}

	pthread_t tid;
	addrsize=sizeof(phoneaddr);

	udp_init( htons( atoi(argv[1]) ) );

	phoneaddr.sin_family = AF_INET;
	phoneaddr.sin_addr.s_addr = inet_addr(argv[2]);//接收方的IP地址
	phoneaddr.sin_port = htons( atoi(argv[3]) );//端口号也需要转换	


	signal(10, signal_cap);
	signal(12, signal_kill);
	
	lcd_init();

	get_picture();//获取 摄像画面  ---》 yuv 压缩为jpeg --》 lcd 显示 发送手机
	

	return 0 ;
}




