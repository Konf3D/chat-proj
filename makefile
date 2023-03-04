TARGET = chatCLI
DIR = ./build
chatcli:
	g++ ./chat-project/main.cpp ./chat-project/user.cpp ./chat-project/db.cpp ./chat-project/gui.cpp
install:
	install $(TARGET) $(DIR)
uninstall:
	rm -rf $(DIR)/$(TARGET)