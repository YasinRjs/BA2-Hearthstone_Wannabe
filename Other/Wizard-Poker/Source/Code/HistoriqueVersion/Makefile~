TARGET=client serveur

normal: $(TARGET)

client: client.cpp
	g++-5 -Wall client.cpp -o client

serveur: serveur.cpp
	g++-5 -Wall serveur.cpp -o serveur

clean:
	$(RM) $(TARGET)
