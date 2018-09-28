all: exc1


exc1: main.o Message.o Client.o Server.o UDPClientSocket.o UDPServerSocket.o UDPSocket.o
	g++ main.o Message.o Client.o Server.o UDPClientSocket.o UDPServerSocket.o UDPSocket.o -o exc1

main.o: main.cpp
	g++ -c main.cpp

Message.o: Message.cpp
	g++ -c Message.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

Server.o: Server.cpp
	g++ -c Server.cpp

UDPClientSocket.o: UDPClientSocket.cpp
	g++ -c UDPClientSocket.cpp

UDPServerSocket.o: UDPServerSocket.cpp
	g++ -c UDPServerSocket.cpp

UDPSocket.o: UDPSocket.cpp
	g++ -c UDPSocket.cpp


clean:
	rm -rf *o exc1
