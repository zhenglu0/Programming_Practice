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
TARGET = BitOperation \
		 BitSetCount \
		 BitSetPosition \
		 BitSwapRequired \
		 CheckEndian \
		 DecToBin \
		 DecToHex \
		 FindMax \
		 FlashingLed \
		 FlipNBit \
		 PowerOf4 \
		 SetClearBit \
		 SwapsTwoInts \
		 UnAndsignedInt

all: $(TARGET)

FlashingLed: FlashingLed.cpp
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) $< -o $@

clean:
	$(RM) $(TARGET)