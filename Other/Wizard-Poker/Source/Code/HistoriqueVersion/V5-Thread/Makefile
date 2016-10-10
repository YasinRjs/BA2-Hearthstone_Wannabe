TARGET=client server

normal: $(TARGET)

client: client.cpp
	g++-5 client.cpp -Wall -o client

server: server.cpp
	g++-5 server.cpp -lpthread -Wall -o server

clean:
	$(RM) $(TARGET)
