all: Project


Project: stegtest.o UDPSocket.o UDPClientSocket.o Client.o  Image.o Message.o
	g++ stegtest.o UDPSocket.o UDPClientSocket.o Client.o  Image.o Message.o -o steg

stegtest.o: stegtest.cpp
	g++ -c stegtest.cpp

Message.o: Message.cpp
	g++ -c -std=c++11 Message.cpp
UDPSocket.o: UDPSocket.cpp
	g++ -c UDPSocket.cpp

UDPClientSocket.o: UDPClientSocket.cpp
	g++ -c UDPClientSocket.cpp

UDPServerSocket.o: UDPServerSocket.cpp
	g++ -c UDPServerSocket.cpp



Image.o: Image.cpp
	g++ -c Image.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

#Server.o: Server.cpp
#	g++ -c Server.cpp




clean:
	rm -rf *o Project
