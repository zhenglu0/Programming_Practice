# Top level makefile, order of lower-level makes matters

WARN := -Wall -Werror
CXXFLAGS := -g ${WARN} 
JOBSERVER := -j 4

all:
	make -C Arrays 			$(JOBSERVER)
	make -C Backtracking	$(JOBSERVER)
	make -C BitManipulation	$(JOBSERVER)
	make -C Concurrency		$(JOBSERVER)
	make -C DataStructure	$(JOBSERVER)
	make -C DP				$(JOBSERVER)
	make -C Geometric		$(JOBSERVER)
	make -C Graphs 			$(JOBSERVER)
	make -C LinkedList		$(JOBSERVER)
	make -C PatternSearch	$(JOBSERVER)
	make -C Recursion		$(JOBSERVER)
	make -C Sorting			$(JOBSERVER)
	make -C Strings			$(JOBSERVER)
	make -C Trees			$(JOBSERVER)
			
clean:
	make -C Arrays 			clean
	make -C Backtracking 	clean
	make -C BitManipulation clean
	make -C Concurrency		clean
	make -C DataStructure 	clean
	make -C DP 				clean
	make -C Geometric 		clean
	make -C Graphs 			clean
	make -C LinkedList 		clean
	make -C PatternSearch	clean
	make -C Recursion 		clean
	make -C Sorting 		clean
	make -C Strings 		clean
	make -C Trees 			clean
