#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED


#ifdef __WIN32__


#include <Windows/ws2_32.c>
#include <memory.c>
#include <reader.c>


static Windows_Sockets windows_sockets = {0};


Boolean initialize_Windows_sockets()
{
	if(!windows_sockets.version) {
		return !WSAStartup(0x0202, &windows_sockets);
	}

	return 1;
}


void deinitialize_Windows_sockets()
{
	if(windows_sockets.version) {
		WSACleanup();
	}

	windows_sockets.version = 0;
}


#define ANY_INTERNET_PROTOCOL     0
#define IPv4                      2
#define IPv6                      23

#define SOCKET_STREAM             1
#define SOCKET_DATAGRAMS          2

typedef enum {
	TCP_PROTOCOL = 6,
	UDP_PROTOCOL = 17
}
Network_Protocol;


typedef struct {
	Byte     family;
	Byte     zero;
	Number16 port;

	union {
		Number32 ip_v4;
		Number32 ip_v6_flow_info;
	};

	Byte ip_v6[16];

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
Address;


Boolean initialize_address(Address* address, Byte* host, Number16 port, Network_Protocol protocol)
{
	Address_Info* address_info;
	Address_Info  hints;
	Byte          port_string[6];

	if(!initialize_Windows_sockets()) {
		goto error;
	}

	clean_bytes(&hints, sizeof(Address_Info));

	if(protocol == UDP_PROTOCOL) {
		hints.family      = IPv4;
		hints.socket_type = SOCKET_DATAGRAMS;
		hints.protocol    = UDP_PROTOCOL;
	}
	else if(protocol == TCP_PROTOCOL) {
		hints.family      = IPv4;
		hints.socket_type = SOCKET_STREAM;
		hints.protocol    = TCP_PROTOCOL;
	}
	else {
		goto error;
	}
	
	
	Byte* port_source = port_string;
	write_Number(&port_source, &write_character_in_bytes, port);
	write_character_in_bytes(&port_source, '\0');

	if(getaddrinfo(host, port_string, &hints, &address_info)) {
		goto error;
	}

	clean_bytes(address, sizeof(Address));
	copy_bytes(address, address_info->address, address_info->address_length);

	freeaddrinfo(address_info);

	return 1;

	error: {
		return 0;
	}
}


Boolean initialize_address_by_url(Address* address, Byte* url)
{
	Number i;
	Byte*  ip;
	
	clean_bytes(address, sizeof(Address));
	
	address->family = IPv4;
	
	ip = &address->ip_v4;
	
	for(i = 0; i < 4; ++i) {
		ip[i] = read_Number(&url, &read_character_from_bytes);
		
		if(url[-1] != '.') {
			if(i != 3 || url[-1] != ':') {
				goto error;
			}
		}
	}
	
	address->port = read_Number(&url, &read_character_from_bytes);
	revert_bytes_order(&address->port, sizeof(address->port));

	return 1;

	error: {
		return 0;
	}
}


void print_address(Address* address)
{
	print_error("%d.%d.%d.%d:%d",
		address->ip_v4 & 0xFF,
		(address->ip_v4 >> 8) & 0xFF,
		(address->ip_v4 >> 16) & 0xFF,
		(address->ip_v4 >> 24) & 0xFF,
		((address->port >> 8) & 0xFF) | ((address->port << 8) & 0xFF00)
	);
}


Socket connect_to_TCP(Address* address)
{
	Socket tcp_socket;

	if(!initialize_Windows_sockets()) {
		goto error;
	}
	
	tcp_socket = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);
	
	if(tcp_socket == -1) {
		goto error;
	}
	
	if(connect(tcp_socket, address, sizeof(Address))) {
		closesocket(tcp_socket);
		goto error;
	}
	
	return tcp_socket;
	
	error: {
		return -1;
	}
}


Number write_bytes_in_TCP(Socket socket, Byte* bytes, Number number_of_bytes)
{
	return send(socket, bytes, number_of_bytes, 0);
}


Number read_bytes_from_TCP(Socket socket, Byte* bytes, Number number_of_bytes)
{
	return recv(socket, bytes, number_of_bytes, 0);
}


Socket connect_to_UDP()
{
	Socket udp_socket;

	if(!initialize_Windows_sockets()) {
		goto error;
	}
	
	udp_socket = socket(IPv4, SOCKET_DATAGRAMS, UDP_PROTOCOL);
	
	if(udp_socket == -1) {
		goto error;
	}
	
	return udp_socket;
	
	error: {
		return -1;
	}
}





Signed_Number write_bytes_in_UDP(Socket socket, Address* address, Byte* bytes, Number number_of_bytes)
{
	return sendto(socket, bytes, number_of_bytes, 0, address, sizeof(Address));
}


Signed_Number read_bytes_from_UDP(Socket socket, Byte* bytes, Number number_of_bytes)
{
	//return recvfrom(socket, bytes, number_of_bytes, 0, 0, 0);
	//return recv(socket, bytes, number_of_bytes, 0);
	
	Signed_Number status;
	
	status = recvfrom(socket, bytes, number_of_bytes, 0, 0, 0);
	
	if(status < 0) {
		print_error("ошибка чтения %d\n", WSAGetLastError());
	}
	
	return status;
}


Boolean bind_to_UDP_server(Socket socket, Address* address)
{
	if(bind(socket, address, sizeof(Address))) {
		goto error;
	}
	
	return 1;
	
	error: {
		return 0;
	}
}


Signed_Number read_bytes_from_UDP_server(Socket socket, Address* client_address, Byte* bytes, Number number_of_bytes)
{
	Number32 client_address_length;
	return recvfrom(socket, bytes, number_of_bytes, 0, client_address, &client_address_length);
}


Signed_Number write_bytes_in_UDP_server(Socket socket, Address* client_address, Byte* bytes, Number number_of_bytes)
{
	return sendto(socket, bytes, number_of_bytes, 0, client_address, sizeof(Address));
}


#endif//__WIN32__


#endif//NETWORK_INCLUDED