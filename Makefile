all:
	g++ -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt

run:
	./tct
	./nasa
	./pdt

try: all run
