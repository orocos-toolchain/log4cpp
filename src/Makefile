CC = g++
LD = g++
INCLUDE = -I../include
CFLAGS = -g -Wall
LIBRARIES =

%.o : %.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $< 

% : %.o
	$(LD) $(CFLAGS) -o $@ $^ $(LIBRARIES)

.PHONY: default all clean

testmain: testmain.o Appender.o FileAppender.o Category.o HierarchyMaintainer.o SimpleLayout.o LoggingEvent.o Priority.o

clean:
	rm *.o
	rm testmain


