all: client_make server_make cp_exec

clean: client_clean server_clean

fclean: clean
	rm -rf ./bin
	rm -rf ./src/client/Babel
	rm -rf ./src/server/server

install:
		sh ./install_script

client_make:
	cd ./src/client;	qmake Babel.pro -r -spec linux-g++-64
	cd -
	make -C ./src/client

server_make:
	make -C ./src/server

cp_exec:
	mkdir -p bin
	cp ./src/server/server ./bin


client_clean:
	cd ./src/client;	qmake Babel.pro -r -spec linux-g++-64
	cd -
	make clean -C ./src/client

server_clean:
	make clean -C ./src/server

