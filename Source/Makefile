TARGET = run

SRCS = render.c terminal.c compiler_b.c compiler.c guide.c motion_lab.c motion_term.c

LIBS = -lSDL2 -lSDL2_ttf -lm

all:
	gcc $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
