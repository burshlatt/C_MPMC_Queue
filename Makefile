.PHONY: build install run uninstall clean

build: uninstall
	@echo --------------------- BUILD ---------------------
	mkdir build
	cd build && cmake ..
	@echo -------------------- SUCCESS --------------------

install:
	@echo -------------------- INSTALL --------------------
	cd build && make
	@echo -------------------- SUCCESS --------------------

run:
	@echo ---------------------- RUN ----------------------
	cd build && ./mpmc_queue
	@echo -------------------- SUCCESS --------------------
	
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

clean: uninstall
