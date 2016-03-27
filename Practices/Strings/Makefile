# the compiler: g++ for C++ program, define as g++ for C++
CXX = g++
CC = gcc
RM = rm -f
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -Wall -Werror
#LDFLAGS = 
SPECIAL_FLAGS = -std=c++0x

# the build target executable:
TARGET = ConvertToWords \
		 IntToStr \
		 LongestSubstring \
		 Palindromes \
		 RemoveCharacters \
		 ReplaceSpace \
		 ReverseNormal \
		 ReverseWords \
		 StrStr \
		 StrToInt \

all: $(TARGET)

StrStr: StrStr.cpp
	$(CXX) $(CXXFLAGS) -Wno-write-strings $< -o $@

clean:
	$(RM) $(TARGET)
