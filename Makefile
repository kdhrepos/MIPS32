CC = gcc

OBJS = main.o \
./stages/fetch.o ./stages/decode.o \
./stages/execute.o ./stages/memory.o ./stages/write_back.o \
./util/print.o \
./hazard/hazard_unit.o ./hazard/forwarding_unit.o 

SRCS = $(OBJS:.o = .c) 

TARGET = mips

$(TARGET) : $(OBJS)
# cd stages; $(MAKE) # move to stages, run make
# cd hazard; $(MAKE) # move to hazard, run make
	$(CC) -o $(TARGET) $(OBJS)
	$(MAKE) clean; # automatically remove object files

#dep : 
#	gccmakedep $(SRCS)

clean :
	rm $(OBJS)
