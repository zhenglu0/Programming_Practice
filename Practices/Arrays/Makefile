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
TARGET = AtoiItoa \
		 DeepestPit \
		 EquilibriumIndex \
		 Intersection2Arrays \
		 MaxDifference \
		 MoreThanHalfNum \
		 NProduct \
		 PartitionNPZ \
		 Presort \
		 PrintMatrixClockwisely \
		 Reorder \
		 RotateImageInplace \
		 Search2DArray \
		 SortedPivotedArray \
		 SumAsMultipleOf3 \
		 TwoNumbersWithSum 

all: $(TARGET)

Presort: Presort.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@

clean:
	$(RM) $(TARGET)
