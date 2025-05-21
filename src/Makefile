all: build

.PHONY: build
build: 
	mkdir -p build && cd build && qmake .. 
	cd build && make

.PHONY: tests
tests:
	gcc ./Test/test.cpp ./Model/Model.cpp -lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra -o tests
	cd ./Test
	./tests
	
.PHONY: install
install: build
	@rm -rf $(HOME)/Desktop/3DViewer_v2.0
	@mkdir $(HOME)/Desktop/3DViewer_v2.0/
	@cp -rf build/View.app  $(HOME)/Desktop/3DViewer_v2.0/
	make clean

.PHONY: clean
clean:
	rm -rf build tests doxygen

.PHONY: uninstall
uninstall:
	@rm -rf build*
	@rm -rf $(HOME)/Desktop/3DViewer_v2.0

.PHONY: style
style:
	clang-format -n -style=Google ./Controller/* ./Model/* ./View/*.cpp ./View/*.h ./engine/*
	clang-format -i -style=Google ./Controller/* ./Model/* ./View/*.cpp ./View/*.h ./engine/*

.PHONY: dvi
dvi:
	doxygen
	open doxygen/html/index.html
	
.PHONY: dist
dist: build
	@rm -rf $(HOME)/Desktop/3DViewer_v2.0.tar
	tar -czf $(HOME)/Desktop/3DViewer_v2.0.tar build/View.app
	make clean