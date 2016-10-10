SRV_OBJS = mainServer.cpp server.cpp card.cpp carddatabase.cpp chatmanager.cpp clientsocket.cpp database.cpp user.cpp usermanager.cpp ranking.cpp matchmaking.cpp gamedeck.cpp player.cpp game.cpp
TARGET=clean echoClean server
CTARGET= server
CC=@g++-5
RM=@rm -f
CFLAGS = -std=c++14 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -Wzero-as-null-pointer-constant
LIBS = -lpthread
TDONE="--- Task completed ---"
DONE="--- All targets have been built and compiled ---"

normal: $(TARGET)

server: mainServer.cpp
	@echo "Compiling server objects..."
	$(CC) $(SRV_OBJS) $(LIBS) $(CFLAGS) -o server
	@echo $(TDONE)
	@echo $(DONE)

echoClean:
	@echo $(TDONE)

clean:
	@echo "Cleaning build targets..."
	$(RM) $(CTARGET)