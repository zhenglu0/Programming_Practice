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
TARGET = AugmentingDS \
  		 BalancedParentheses \
		 ClosedHashing \
		 FirstNonRepeated \
		 HashingAChar \
		 IntervalTree \
		 IsAnagram \
		 KLargestSum \
		 LargestNNumbers \
		 LargestRectangular \
		 LRUCache \
		 MedianHeap \
		 MergeTime \
		 OpenHashing \
		 RedBlackTree
		 
all: $(TARGET)

FirstNonRepeated: FirstNonRepeated.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@

KLargestSum: KLargestSum.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@

clean:
	$(RM) $(TARGET)