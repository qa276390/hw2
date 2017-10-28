.PHONY:clean

Poly: b04505026.cpp Poly.h
	g++ -o Poly -std=c++11 b04505026.cpp Poly.h

clean:
	rm -f Poly
