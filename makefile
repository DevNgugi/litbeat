CXX = g++
CXXFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`
CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a -lrt -lasound -ljack -pthread

SRC = src/main.cpp src/MyApp.cpp src/MyFrame.cpp src/AudioHandler.cpp

INCLUDE = -I./include

TARGET = build/litbeat

$(TARGET): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(TARGET) $(SRC) $(LDFLAGS) $(CLIB)

dev: $(TARGET)
	@mkdir -p build
	./$(TARGET)

install-deps:
	mkdir -p lib 
	curl https://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz | tar -zx -C lib
	cd lib/portaudio && ./configure && $(MAKE) -j 

.PHONY: install-deps

uninstall-deps:
	cd lib/portaudio && $(MAKE) uninstall
	rm -rf lib/portaudio

.PHONY: uninstall-deps

clean:
	rm -f build/$(TARGET)

.PHONY: clean
