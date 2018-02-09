simple_sh: simple_sh.h simple_sh.c prompt.c interpret_input.c built_in.c add_history.c s2i.c clear_history.c interpret_line.c builtin_pipe.c
	gcc -Wall simple_sh.c prompt.c interpret_input.c built_in.c add_history.c s2i.c clear_history.c interpret_line.c builtin_pipe.c -o simple_sh
test: simple_sh.h test.c prompt.c interpret_input.c
	gcc -Wall test.c prompt.c interpret_input.c -o test
hello_world: hello_world.c
	gcc -Wall hello_world.c -o hello_world
clean: 
	rm -f simple_sh hello_world test
