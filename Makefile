all : splitter

splitter : Driver.cpp Dictionary.o SplitUtils.o
	g++ -g Driver.cpp Dictionary.o SplitUtils.o -o splitter  
	
Dictionary.o : Dictionary.h
	g++ -c Dictionary.cpp -o Dictionary.o

SplitUtils.o : SplitUtils.h
	g++ -c SplitUtils.cpp -o SplitUtils.o
	
clean: 
	rm ./*.o
	rm ./splitter
