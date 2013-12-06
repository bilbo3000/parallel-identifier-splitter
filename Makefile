all : splitter

splitter : Driver.cpp Utils.o Dictionary.o SplitUtils.o 
	g++ -g Driver.cpp Utils.o Dictionary.o SplitUtils.o -o splitter  

Utils.o : Utils.h
	g++ -c Utils.cpp -o Utils.o
		
Dictionary.o : Dictionary.h
	g++ -c Dictionary.cpp -o Dictionary.o

SplitUtils.o : SplitUtils.h
	g++ -c SplitUtils.cpp -o SplitUtils.o
	
clean: 
	rm -rf ./*.o
	rm -rf ./splitter
