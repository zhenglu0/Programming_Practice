# the compiler: g++ for C++ program, define as g++ for C++
CXX = g++
CC = gcc
RM = rm -f
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -Wall -Werror
LDFLAGS = 
SPECIAL_FLAGS = -std=c++0x
LIBS = -lpthread
# the build target executable:
TARGET = Atomic_Wait \
		 Concurrency \
		 Count \
		 LockFree \
		 Sync \
		 ThreadSafeList

all: $(TARGET)

Atomic_Wait: Atomic_Wait.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@ $(LIBS)

Concurrency: Concurrency.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@ $(LIBS)

Count: Count.c
	$(CC) $(CXXFLAGS) $< -o $@ $(LIBS)

LockFree: LockFree.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@ $(LIBS)

Sync: Sync.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@ $(LIBS)
	
ThreadSafeList: ThreadSafeList.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@ $(LIBS)

clean:
	$(RM) $(TARGET)
