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
TARGET = MorrisTraversal \
		 NodesNoSibling \
		 SortedListToBST \
		 SquenceOfBSTVerify \
		 TreeDistanceK \
		 TreeHasSubtree \
		 TreeLCA \
		 TreeOperation \
		 TreeProperty \
		 TreeSerialAndDe \
		 TreeTraversal 

all: $(TARGET)

clean:
	$(RM) $(TARGET) *.txt *.o

LAB9_EXE  = HW
LAB9_OBJS = HW.o Functions.o

###

TreeHasSubtree: TreeHasSubtree.o TreeCommon.o
	$(CXX) $(CXXFLAGS) $(SPECIAL_FLAGS) -o $@ $^

TreeLCA: TreeLCA.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TreeOperation: TreeOperation.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TreeProperty: TreeProperty.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TreeTraversal: TreeTraversal.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TreeDistanceK: TreeDistanceK.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TreeSerialAndDe: TreeSerialAndDe.o TreeCommon.o
	$(CXX) $(CXXFLAGS) -o $@ $^

###

.cpp.o:
	$(CXX) $(SPECIAL_FLAGS) $(CXXFLAGS) -c $<

###

TreeCommon.o: TreeCommon.cpp TreeCommon.h
TreeHasSubtree.o: TreeHasSubtree.cpp TreeCommon.cpp TreeCommon.h
TreeLCA.o: TreeLCA.cpp TreeCommon.cpp TreeCommon.h
TreeOperation.o: TreeOperation.cpp TreeCommon.cpp TreeCommon.h
TreeProperty.o: TreeProperty.cpp TreeCommon.cpp TreeCommon.h
TreeTraversal.o: TreeTraversal.cpp TreeCommon.cpp TreeCommon.h
TreeDistanceK.o: TreeDistanceK.cpp TreeCommon.cpp TreeCommon.h
TreeSerialAndDe.o: TreeSerialAndDe.cpp TreeCommon.cpp TreeCommon.h