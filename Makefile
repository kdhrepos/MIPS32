CC = gcc

OBJS = main.o \
./stages/common.o ./stages/fetch.o ./stages/decode.o \
./stages/execute.o ./stages/memory.o ./stages/write_back.o
SRCS = $(OBJS:.o = .c) 

TARGET = mips

$(TARGET) : $(OBJS)
	cd stages; $(MAKE) # move to stages, run make
	$(CC) -o $(TARGET) $(OBJS)

# dep : 
# 	gccmakedep $(SRCS)

clean :
	cd stages; $(MAKE) clean # move to stages, run make clean
	rm $(OBJS)
