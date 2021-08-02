CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/Exception.o: raw_logic/Exception.cpp raw_logic/Exception.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/UserModel.o: raw_logic/UserModel.cpp raw_logic/UserModel.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/UserModel.cpp -o $(BUILD_DIR)/UserModel.o

$(BUILD_DIR)/Normal_User.o: raw_logic/Normal_User.cpp raw_logic/Normal_User.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Normal_User.cpp -o $(BUILD_DIR)/Normal_User.o


$(BUILD_DIR)/Filters.o: raw_logic/Filters.cpp raw_logic/Filters.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Filters.cpp -o $(BUILD_DIR)/Filters.o

$(BUILD_DIR)/Order.o: raw_logic/Order.cpp raw_logic/Order.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Order.cpp -o $(BUILD_DIR)/Order.o

$(BUILD_DIR)/outerior_functions.o: raw_logic/outerior_functions.cpp raw_logic/outerior_functions.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/outerior_functions.cpp -o $(BUILD_DIR)/outerior_functions.o

$(BUILD_DIR)/Shelf.o: raw_logic/Shelf.cpp raw_logic/Shelf.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Shelf.cpp -o $(BUILD_DIR)/Shelf.o

$(BUILD_DIR)/Supplier.o: raw_logic/Supplier.cpp raw_logic/Supplier.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Supplier.cpp -o $(BUILD_DIR)/Supplier.o

$(BUILD_DIR)/Offer.o: raw_logic/Offer.cpp raw_logic/Offer.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/Recipe.o: raw_logic/Recipe.cpp raw_logic/Recipe.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Recipe.cpp -o $(BUILD_DIR)/Recipe.o

$(BUILD_DIR)/Score.o: raw_logic/Score.cpp raw_logic/Score.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Score.cpp -o $(BUILD_DIR)/Score.o

$(BUILD_DIR)/Chef.o: raw_logic/Chef.cpp raw_logic/Chef.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c raw_logic/Chef.cpp -o $(BUILD_DIR)/Chef.o

$(BUILD_DIR)/data_root.o: data_root.cpp data_root.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c data_root.cpp -o $(BUILD_DIR)/data_root.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o


$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/UserModel.o $(BUILD_DIR)/Shelf.o $(BUILD_DIR)/Supplier.o $(BUILD_DIR)/Score.o $(BUILD_DIR)/Recipe.o $(BUILD_DIR)/outerior_functions.o $(BUILD_DIR)/Normal_User.o $(BUILD_DIR)/Chef.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Order.o $(BUILD_DIR)/Filters.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/main.o $(BUILD_DIR)/data_root.o  $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o  $(BUILD_DIR)/UserModel.o $(BUILD_DIR)/Shelf.o $(BUILD_DIR)/Supplier.o $(BUILD_DIR)/Score.o $(BUILD_DIR)/Recipe.o $(BUILD_DIR)/outerior_functions.o $(BUILD_DIR)/Normal_User.o $(BUILD_DIR)/Chef.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Order.o $(BUILD_DIR)/Filters.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/main.o $(BUILD_DIR)/data_root.o  $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
