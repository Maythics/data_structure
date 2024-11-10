all:
	g++ test.cpp -o test -O2

run: all
	time ./test

report:
	xelatex report.tex
clean:
	rm test report.pdf report.aux report.log
