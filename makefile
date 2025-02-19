flags = -I /opt/homebrew/include -L /opt/homebrew/lib -std=c++20 -Wall -Wextra -Werror -pedantic
targets = main.cpp 
make: $(targets)
	g++ $(targets) $(flags)