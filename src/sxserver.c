#include <winsock2.h>
#include <windows.h>

int main() {
  WSADATA wsadata;
  WSAStartup(MAKEWORD(2, 2), &wsadata);
  return 0;
}
