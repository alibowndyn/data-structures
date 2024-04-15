CC 	   := gcc
SRCS   := $(wildcard *.c *.h)
TARGET := main


.PHONY: all vis clean
all: $(TARGET)


$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET)
	./$(TARGET)

vis: $(TARGET)
	./$(TARGET) | dot -Tpdf > vis.pdf

clean:
	rm -f $(TARGET)
