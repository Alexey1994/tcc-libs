#ifndef SYSTEM_WINDOWS_WS2_32_INCLUDED
#define SYSTEM_WINDOWS_WS2_32_INCLUDED


#include <types.c>


//=============================== WSA ================================


typedef struct {
	Number16 version;
	Number16 high_version;
	Byte     description[257];
	Byte     system_status[129];
	Number32 maximum_sockets;
	Number32 maximum_UDP_size;
	Byte*    vendor_info;
}
Windows_Sockets;

import stdcall Number32 WSAStartup(Number16 version, Windows_Sockets* sockets);
import stdcall Number32 WSACleanup();
import stdcall Number32 WSAGetLastError();


//=============================== Address Info =======================


typedef struct {
	Byte  family;
	Byte  zero;
	Number16 port;

	union {
		Number32 ip_v4;
		Number32 ip_v6_flow_info;
	};

	Number8 ip_v6[16];

	union {
		Number32 ip_v6_scope_id;

		union {
			struct {
				Number32 zone: 28;
				Number32 level: 4;
			};

			Number32 value;
		};
	};
}
Windows_Address;


typedef struct {
	Number32             flags;
	Number32             family;
	Number32             socket_type;
	Number32             protocol;
	Number               address_length;
	Byte*                name;
	Windows_Address*     address;
	struct Address_Info* next;
}
Address_Info;

import stdcall Address_Info* getaddrinfo  (Byte* host, Byte* port, Address_Info* hints, Address_Info** result);
import stdcall void          freeaddrinfo (Address_Info* address_info);


//=============================== Socket =============================

typedef Signed_Number32 Socket;

import stdcall Socket          socket      (Number32 family, Number32 type, Number32 protocol);
import stdcall Signed_Number32 closesocket (Socket socket);
import stdcall Signed_Number32 connect     (Socket socket, Windows_Address* address, Number32 address_length);
import stdcall Signed_Number32 bind        (Socket socket, Windows_Address* address, Number32 address_length);
import stdcall Signed_Number32 send        (Socket socket, Byte* buffer, Number32 buffer_length, Number32 flags);
import stdcall Signed_Number32 sendto      (Socket socket, Byte* buffer, Number32 buffer_length, Number32 flags, Windows_Address* destination_address, Number32 destination_address_length);
import stdcall Signed_Number32 recv        (Socket socket, Byte* buffer, Number32 buffer_length, Number32 flags);
import stdcall Signed_Number32 recvfrom    (Socket socket, Byte* buffer, Number32 buffer_length, Number32 flags, Windows_Address* destination_address, Number32* destination_address_length);
import stdcall Socket          accept      (Socket socket, Windows_Address* address, Number32 address_length);
import stdcall Signed_Number32 listen      (Socket socket, Number32 maximum_pending_connections);
import stdcall Signed_Number32 ioctlsocket (Socket socket, Number32 command, Number32* arguments);


#endif //SYSTEM_WINDOWS_WS2_32_INCLUDED