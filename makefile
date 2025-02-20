flags = -I /opt/homebrew/include -L /opt/homebrew/lib -std=c++20 -Wall -Wextra  -Werror -pedantic -g3
targets = main.cpp 
make: $(targets)
	g++ $(targets) $(flags)