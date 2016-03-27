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
TARGET = EightQueen \
		 GraphColoring \
		 Hamiltonian \
		 Knight \
		 Knight_tour \
		 RatInMaze \
		 SubsetSum \
		 SudokuSolving
		 
all: $(TARGET)

clean:
	$(RM) $(TARGET)