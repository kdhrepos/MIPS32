CC = gcc

OBJS = fetch.o decode.o execute.o memory.o write_back.o
SRCS = $(OBJS:.o = .c)

TARGET = obj

$(TARGET) : $(SRCS)
	$(CC) -c $(SRCS)

clean :
	rm $(OBJS)
