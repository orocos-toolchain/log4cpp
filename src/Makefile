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

testmain: testmain.o Appender.o FileAppender.o Category.o HierarchyMaintainer.o BasicLayout.o LoggingEvent.o Priority.o NDC.o

testNDC: testNDC.o NDC.o

clean:
	rm *.o
	rm testmain
	rm testNDC


