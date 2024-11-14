#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <string.h>

#define true 1
#define false 0;

int main() {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(server_socket, (SOCKADDR *)&server_address, sizeof(server_address));
	listen(server_socket, SOMAXCONN);

	struct sockaddr_in client_address;
	int client_size = sizeof(client_address);
    SOCKET client_socket = accept(server_socket,
                                  (SOCKADDR *)&client_address,
                                  &client_size);

	char host[NI_MAXHOST] = {0};
	char service[NI_MAXSERV] = {0};

	if (getnameinfo((SOCKADDR*)&client_address, client_size, host, NI_MAXHOST, service,NI_MAXSERV, 0) == 0) {
		printf("%s connected on port %s\n", host, service);
	} else {
		inet_ntop(AF_INET, &client_address.sin_addr, host, NI_MAXHOST);
		printf("%s connected on port %hu\n", host, ntohs(client_address.sin_port));
	}

	//closesocket(server_socket);

	/*
	char buffer[256];
	while (true) {
		ZeroMemory(buffer, 256);
		int bytes_received = recv(client_socket, buffer, 256, 0);
		if (bytes_received == SOCKET_ERROR) {
			printf("Error received  Shutting down...\n");
			break;
		}

		if (!bytes_received) {
			printf("Client disconnected\n");
			break;
		}

		send(client_socket, buffer, bytes_received + 1, 0);
	}
	*/

 	//closesocket(client_socket);
	
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
