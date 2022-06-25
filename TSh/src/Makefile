
CXXFLAGS ?= -g -Wall -Wextra -Werror

TSH: repl
	@mv Termi-Shell out
	@out/Termi-Shell

repl: repl.cpp
	$(CXX) $(CXXFLAGS) -o Termi-Shell repl.cpp

clean:
	rm -rf out/*
