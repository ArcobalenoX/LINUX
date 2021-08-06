/*********Packgage function myheader****/
#include "PackageC.h"



int main(int argc,char **argv)
{

	// ./main  <port>  <ip>
	if(argc != 2){
	
		printf("usage: %s <port>\n", argv[0]);
		exit(-1);
	}

	//udp init
	int fd_udp = Socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in udp_addr;
	udp_addr.sin_family = 	AF_INET;
	udp_addr.sin_port = htons(atoi(argv[1]));
	udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len_addr = sizeof(udp_addr);

	Bind(fd_udp, (struct sockaddr *)&udp_addr, len_addr);

	//接受显示
	lcd_init();

	struct sockaddr_in rcv_addr;
	char buf[640*480*3];
	ssize_t size_rcv;
	while(1){
		
		memset(buf, 0, 640*480*3);
		size_rcv = recvfrom(fd_udp, buf, 640*480*3, 0, \
			   (struct sockaddr *)&rcv_addr, &len_addr);
		
		if(size_rcv == -1){
			printf("recv jpg err\n");
		}
		
		// printf("recv: %lu\n", size_rcv);

		int tp = ntohs(rcv_addr.sin_port);
		if(tp%10 == 1){
			// printf("show\n");
			jpeg_show_buf(buf, size_rcv, 0, 0, 1);
		}
		
	}

	return 0;
}//end of te main


