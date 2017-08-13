all:
	cd src; make
	cd qsrc; make
	cd test; make
	cd qtest; make

clean:
	cd src; make clean
	cd qsrc; make clean
	cd test; make clean
	cd qtest; make clean
