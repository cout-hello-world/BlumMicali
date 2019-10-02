CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -O3
LDLIBS = -lgmp

rng: blum_micali.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

main.o: main.cc blum_micali.hh
	$(CXX) -c $(CXXFLAGS) -o $@ $<

blum_micali.o: blum_micali.cc pi.inc blum_micali.hh
	$(CXX) -c $(CXXFLAGS) -o $@ $<

pi.inc: make_pi.py
	python3 $<
