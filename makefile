TARGET = chatcli
DIR = ./build/chatCLI
chatcli:
	g++ ./chat-project/main.cpp ./chat-project/user.cpp ./chat-project/db.cpp ./chat-project/gui.cpp -o $(DIR)
install:
	install $(TARGET) $(DIR)
uninstall:
	rm -rf $(DIR)/$(TARGET)