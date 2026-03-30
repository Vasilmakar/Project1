FLAGS=-std=c++17 -Wall -Wextra -Werror

# Create library if Parameters.cpp and/or .h has changed.
libparameters.so: Parameters.cpp Parameters.h
	g++ $(FLAGS) -shared -fPIC Parameters.cpp -o libparameters.so

# Remove object file and the library itself.
clean:
	rm -f Parameters.o libparameters.so

