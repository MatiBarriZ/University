CPP = g++
CFLAGS = -Wall -I$(INC_DIR)
INC_DIR = ../inc
OBJ_DIR = ../obj
BIN_DIR = ../bin
SRC_DIR = ../src
TARGET_BST = $(BIN_DIR)/BST
TARGET_CHT = $(BIN_DIR)/CHT
TARGET_OHT = $(BIN_DIR)/OHT
TARGET_SET = $(BIN_DIR)/SET
TARGET_USET = $(BIN_DIR)/USET
BST_OBJS = $(OBJ_DIR)/mainBST.o $(OBJ_DIR)/BinarySearchTree.o
CHT_OBJS = $(OBJ_DIR)/mainCHT.o $(OBJ_DIR)/ClosedHashing.o
OHT_OBJS = $(OBJ_DIR)/mainOHT.o $(OBJ_DIR)/OpenHashing.o
SET_OBJS = $(OBJ_DIR)/mainSET.o
USET_OBJS = $(OBJ_DIR)/mainUSET.o

all: $(TARGET_BST) $(TARGET_CHT) $(TARGET_OHT) $(TARGET_SET) $(TARGET_USET)

##SET
$(TARGET_SET): $(SET_OBJS)
	mkdir -p $(OBJ_DIR)
	$(CPP) $(SET_OBJS) -o $(TARGET_SET) -lm

$(OBJ_DIR)/mainSET.o: $(SRC_DIR)/mainSET.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/mainSET.cpp -o $(OBJ_DIR)/mainSET.o

##USET
$(TARGET_USET): $(USET_OBJS)
	mkdir -p $(OBJ_DIR)
	$(CPP) $(USET_OBJS) -o $(TARGET_USET) -lm

$(OBJ_DIR)/mainUSET.o: $(SRC_DIR)/mainUSET.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/mainUSET.cpp -o $(OBJ_DIR)/mainUSET.o
	
##BinarySearchTree
$(TARGET_BST): $(BST_OBJS)
	mkdir -p $(BIN_DIR)
	$(CPP) $(BST_OBJS) -o $(TARGET_BST) -lm

$(OBJ_DIR)/mainBST.o: $(SRC_DIR)/mainBST.cpp $(INC_DIR)/BinarySearchTree.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/mainBST.cpp -o $(OBJ_DIR)/mainBST.o

$(OBJ_DIR)/BinarySearchTree.o: $(SRC_DIR)/BinarySearchTree.cpp $(INC_DIR)/BinarySearchTree.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/BinarySearchTree.cpp -o $(OBJ_DIR)/BinarySearchTree.o

##ClosedHashing
$(TARGET_CHT): $(CHT_OBJS)
	mkdir -p $(BIN_DIR)
	$(CPP) $(CHT_OBJS) -o $(TARGET_CHT) -lm

$(OBJ_DIR)/mainCHT.o: $(SRC_DIR)/mainCHT.cpp $(INC_DIR)/ClosedHashing.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/mainCHT.cpp -o $(OBJ_DIR)/mainCHT.o

$(OBJ_DIR)/ClosedHashing.o: $(SRC_DIR)/ClosedHashing.cpp $(INC_DIR)/ClosedHashing.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/ClosedHashing.cpp -o $(OBJ_DIR)/ClosedHashing.o

##OpenHashing
$(TARGET_OHT): $(OHT_OBJS)
	mkdir -p $(BIN_DIR)
	$(CPP) $(OHT_OBJS) -o $(TARGET_OHT) -lm

$(OBJ_DIR)/mainOHT.o: $(SRC_DIR)/mainOHT.cpp $(INC_DIR)/OpenHashing.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/mainOHT.cpp -o $(OBJ_DIR)/mainOHT.o

$(OBJ_DIR)/OpenHashing.o: $(SRC_DIR)/OpenHashing.cpp $(INC_DIR)/OpenHashing.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) -c $(CFLAGS) $(SRC_DIR)/OpenHashing.cpp -o $(OBJ_DIR)/OpenHashing.o

.PHONY: clean

clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)

