SRC=Logger.cpp demo.cpp

debug:
	g++ -o Logger $(SRC) -Wall -g -DDEBUG

release:
	g++ -o Logger $(SRC) -Wall 
	strip -x -s Logger

lib:
	g++ -fPIC -c Logger.cpp -Wall
	g++ -o liblogger.so.1.0.0 Logger.o -shared -Wl,-soname,liblogger.so
	strip liblogger.so.1.0.0

clean:
	rm -rf Logger Logger.o liblogger.so.1.0.0
