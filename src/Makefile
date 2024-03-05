CC = g++ -std=c++17
FLAGS = -Wall -Werror -Wextra
GTESTFLAG = -lgtest

SRC_BACK_DIR = back
SRC_CONTROLLER_DIR = controller
SRC_BACK_DIR_FILES = $(wildcard $(SRC_BACK_DIR)/*.cc)
SRC_CONTROLLER_DIR_FILES = $(wildcard $(SRC_CONTROLLER_DIR)/s21_*.cc)
ALL_FILES = $(SRC_BACK_DIR_FILES) $(SRC_CONTROLLER_DIR_FILES)
TEST_BUILD_FOLDER = build

SRC_FRONT_DIR = view
QT_PROJECT_NAME = maze
QT_PROJECT_FOLDER = ./$(SRC_FRONT_DIR)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = qt_build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = MAZE
TAR_DIR = $(QT_PROJECT_NAME)_Archive

OS_NAME = $(shell uname -s)
TAR_DIR = Viewer.0_Archive

ifeq ($(OS_MAME), Linux)
	LFLAGS += -lrt -lsubunit -lm
endif

.PHONY: all

all: test install dist dvi

install: generate_make
	@echo "Building application..."
	cd ./$(QT_BUILD_FOLDER) && make -s -f $(QT_MAKEFILE)
	@echo "Application builded."
	@echo  "Moving application to folder \"$(QT_APP_FOLDER)\"..." -n
	rm -rf ./$(QT_APP_FOLDER)
	mkdir -p ./$(QT_APP_FOLDER)
ifeq ($(OS_NAME), Linux) 
	mv $(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ../App 
endif 
ifeq ($(OS_NAME), Darwin)
	mv $(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app ../App 
endif
	@echo "Done."
	@echo "Deleting build folder..."
	rm -rf $(QT_BUILD_FOLDER)
	@echo "Done."
	@echo "Installation complete!"

generate_make:
	qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	rm -rf .qmake.stash

uninstall:
	@echo "Uninstalling application..."
	rm -rf $(QT_APP_FOLDER)
	@echo "Done"

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp -R  $(SRC_FRONT_DIR) $(TAR_DIR)/src
	cp -R  $(SRC_BACK_DIR) $(TAR_DIR)/src
	cp -R  $(SRC_CONTROLLER_DIR) $(TAR_DIR)/src
	cp -R  Doxyfile Makefile $(TAR_DIR)/src
	tar cvzf $(QT_PROJECT_NAME).tgz $(TAR_DIR)
	mv $(QT_PROJECT_NAME).tgz ..
	rm -Rf $(TAR_DIR)

dvi:
	doxygen Doxyfile
	open documentation/html/index.html


style:
	clang-format -style=Google -n back/*.cc back/*.h
	clang-format -style=Google -n view/*.cc view/*.h
	clang-format -style=Google -n controller/*.cc controller/*.h

test:
	make clean
	mkdir $(TEST_BUILD_FOLDER)
	for i in $(SRC_BACK_DIR_FILES); \
	do \
		$(CC) $(FLAGS) -c $$i; \
	done;

	mv *.o $(TEST_BUILD_FOLDER)
	$(CC) $(FLAGS) $(TEST_BUILD_FOLDER)/*.o -o $(TEST_BUILD_FOLDER)/test $(GTESTFLAG) 
	./$(TEST_BUILD_FOLDER)/test

clean:
	rm -rf $(TEST_BUILD_FOLDER)
	rm -rf $(QT_BUILD_FOLDER)
	rm -rf build-maze-Desktop_arm_darwin_generic_mach_o_64bit-Debug
	rm -rf $(QT_PROJECT_NAME).0_Archive
	rm -rf ../$(QT_PROJECT_NAME).tgz

rebuild:
	make clean
	make all