CC = g++
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = .
LIB_DIR = ../lib
BIN_DIR = ../bin

all: $(BIN_DIR)/CCsvTest

SRC = \
CCsvTest.cpp

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++11 \
-I$(INC_DIR) \
-I. \
-I../../CStrUtil/include \
-I../../CUtil/include \

LFLAGS = \
-L$(LIB_DIR) \
-L../../CStrUtil/lib \

clean:
	$(RM) -f *.o
	$(RM) -f CCsvTest

.SUFFIXES: .cpp

.cpp.o:
	$(CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

$(BIN_DIR)/CCsvTest: $(OBJS)
	$(CC) $(LDEBUG) -o $(BIN_DIR)/CCsvTest $(OBJS) $(LFLAGS) -lCStrUtil
