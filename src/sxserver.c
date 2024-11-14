#include <winsock2.h>

#include <stdio.h>
#include <string.h>

int main() {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = 0;
	address.sin_port = htons(8080);
	bind(server_socket, (SOCKADDR *)&address, sizeof(address));

	listen(server_socket, 10);
	SOCKET client_socket = accept(server_socket, 0, 0);

	char request[256] = {0};
	recv(client_socket, request, 256, 0);

	if (memcmp(request, "GET / ", 6) == 0) {
		FILE *file = fopen("src/index.html", "r");
		char buffer[256] = {0};
		fread(buffer, 1, 256, file);
		send(client_socket, buffer, 256, 0);
	}

	WSACleanup();
	return 0;
}
