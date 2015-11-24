compile:
	mkdir -p build
	cd build && cmake .. && make

clean:
	rm -r build/

run:
	build/glowing-octo-batman
