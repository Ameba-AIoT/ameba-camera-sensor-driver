#if 0
#include <lwip/sockets.h>

#define SERVER_PORT_NUM 6000
#define TX_SIZE 65536

#define SENDER_PORT_NUM 6001
#define SENDER_IP_ADDR "192.168.1.168"

int send_frame_init(char *ipaddr)
{
	int socket_fd=-1;
	struct sockaddr_in sa,ra;

	/* Creates an TCP socket (SOCK_STREAM) with Internet Protocol Family (PF_INET).
	 * Protocol family and Address family related. For example PF_INET Protocol Family and AF_INET family are coupled.
	*/
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);

	if ( socket_fd < 0 ) {
		printf("socket call failed");
		socket_fd = -1;
		goto exit;
	}

	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(SENDER_IP_ADDR);
	sa.sin_port = htons(SENDER_PORT_NUM);
	
	/* Bind the TCP socket to the port SENDER_PORT_NUM and to the current
	* machines IP address (Its defined by SENDER_IP_ADDR).
	* Once bind is successful for UDP sockets application can operate
	* on the socket descriptor for sending or receiving data.
	*/
	if (bind(socket_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1) {
		printf("Bind to Port Number %d ,IP address %s failed\n",SENDER_PORT_NUM,SENDER_IP_ADDR);
		close(socket_fd);
		socket_fd = -1;
		goto exit;
	}

	/* Receiver connects to server ip-address. */
	memset(&ra, 0, sizeof(struct sockaddr_in));
	ra.sin_family = AF_INET;
	ra.sin_addr.s_addr = inet_addr(ipaddr);
	ra.sin_port = htons(SERVER_PORT_NUM);
	
	if(connect(socket_fd,(struct sockaddr*)&ra,sizeof(struct sockaddr_in)) < 0) {
		printf("connect failed \n");
		close(socket_fd);
		socket_fd = -1;
		goto exit;
	}

exit:
	return socket_fd;
}

static int send_block(int socket_fd, char *ptr, int size)
{
	int sent_data, i; 
	int ret = 0;

	i = 0;
	while (size > TX_SIZE) {
		sent_data = send(socket_fd, &ptr[i], TX_SIZE, 0);
		if(sent_data < 0 ) {
			printf("send failed\n");
			close(socket_fd);
			ret = -5;
			goto exit;
		}
		size -= TX_SIZE;
		i += TX_SIZE;
		if ((i%TX_SIZE)==0)
			printf("+");
	}
	
	if (size) {
		sent_data = send(socket_fd, &ptr[i], size, 0);
		if(sent_data < 0 ) {
			printf("send failed\n");
			close(socket_fd);
			ret = -5;
			goto exit;
		}
	}

exit:
	return ret;
}

int send_to_host(int socket_fd, char *ptrY, int sizeY, int offset_uv, int sizeUV)
{
	int total_size;
	int sent_data;
	int ret = 0;

	total_size = sizeY + sizeUV;
	sent_data = send(socket_fd, &total_size, 4, 0);
	if(sent_data < 0 ) {
		printf("send size failed\n");
		close(socket_fd);
		ret = -4;
		goto exit;
	}

	printf("send Y:(0x%08x, %d) UV:(0x%08x, %d)\n", (unsigned int)ptrY, sizeY,
													(unsigned int)ptrY + offset_uv, sizeUV);
	//Y
	ret = send_block(socket_fd, ptrY, sizeY);
	if (ret) goto exit;
	//UV
	ret = send_block(socket_fd, &ptrY[offset_uv], sizeUV);
	if (ret) goto exit;

	printf("\nsend frame complete\n");

	//close(socket_fd);

exit:
	return ret;
}
#endif
