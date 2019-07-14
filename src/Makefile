PROJECT=xengine

CXX=g++
CXXFLAGS=-W -std=c++11 -g
LINK=-Wl,-rpath,$(JEMALLOC_DIR)/lib

LIB_DIR:=lib
INC_DIR:=include
THIRD_PART_DIR:=3rd
PROTO_DIR:=$(THIRD_PART_DIR)/protobuf
MONGOC_DIR:=$(THIRD_PART_DIR)/mongo-c-driver
BSON_DIR:=$(THIRD_PART_DIR)/mongo-c-driver
MSGPACK_DIR:=$(THIRD_PART_DIR)/msgpack
JEMALLOC_DIR:=$(THIRD_PART_DIR)/jemalloc

INC_FILES:=-I$(INC_DIR) \
	-I$(LIB_DIR)/include \
	-I$(PROTO_DIR)/include\
	-I$(MONGOC_DIR)/include/libmongoc-1.0\
	-I$(BSON_DIR)/include/libbson-1.0\
	-I$(MSGPACK_DIR)/include/\
	-I/usr/include/python3.5

SRC_DIR=common \
	gamed

#CXX_SRC_FILES:=$(foreach v, $(SRC_DIR), $(wildcard $(v)/*.cpp))
CXX_SRC_FILES:=common/


CXX_OBJ_FILES:=$(subst .cpp,.o,$(CXX_SRC_FILES))

LIBS=-L$(LIB_DIR)/lib \
	-L$(PROTO_DIR)/lib \
	-L$(MONGOC_DIR)/lib \
	-L$(MSGPACK_DIR)/lib \
	-L$(JEMALLOC_DIR)/lib

STATIC_LIBS= -lpython3.5m \
	-lprotobuf \
	-lmongoc-1.0 \
	-lbson-1.0 \
	-ljemalloc \
	-lmsgpackc

$(CXX_OBJ_FILES):$(CXX_SRC_FILES)
	echo $(CXX_SRC_FILES)
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(INC_FILES) $(LIBS) $(STATIC_LIBS)

all: $(CXX_OBJ_FILES)
	#echo $(CXX_SRC_FILES)
	$(CXX) $(CXXFLAGS) $(CXX_OBJ_FILES) -o $(PROJECT)


.PHONY:clean rpc
clean:
	-rm $(PROJECT)
	-rm -rf $(SRC_DIR)/*.o
rpc:
	@python tools/parse_rpc.py
