# the compiler: g++ for C++ program, define as g++ for C++
CXX = g++
RM = rm -f
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -Wall -Werror
#LDFLAGS = 
SPECIAL_FLAGS = -std=c++0x

# the build target executable:
TARGET = BucketSort \
		 CountingSort \
		 DeterministicSelect \
		 HeapSort \
		 MergeSort \
		 PancakeSort \
		 RandomizedSelect \
		 QuickSort \
		 RadixSort \
		 TopologicalSort \

all: $(TARGET)

FirstNonRepeated: FirstNonRepeated \n
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@

clean:
	$(RM) $(TARGET)