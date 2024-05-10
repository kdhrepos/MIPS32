CC = gcc

OBJTS = stages.o main.o
SRCS = $(OBJTS:.o = .c) # Macro subtitution
TARGET = mips

$(TARGET) : $(OBJTS)
	$(CC) -o $(TARGET) $(OBJTS)

dep : 
	gccmakedep $(SRCS)

clean :
	rm $(OBJTS)
