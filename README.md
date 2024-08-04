# litbeat
An open source Audio manipulation Program in C++

<!-- https://youtu.be/jpsJCji71Ec -->
<!-- https://youtu.be/yt7i4zPbVDs -->

Install dependencies on linux

```
sudo apt-get install cmake clang pulseaudio libasound-dev libjack-dev

make install-deps #from our custom make file

#Dependencies for wxwidget

sudo apt install build-essential
sudo apt install libgtk2.0-dev             
sudo apt install libgtk-3-dev

wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.5/wxWidgets-3.2.5.tar.bz2
tar -xvjf wxWidgets-3.2.5.tar.bz2

mkdir gtk-build             # the name is not really relevant
cd gtk-build
../configure                # builds unicode, shared lib
make -j3                    # use 3 cores. Set to the number of cores you have. 'make' uses 1 core
sudo make install           # some platforms require to use 'su' instead of 'sudo'
sudo ldconfig 

Test:
wx-config --version 

#WIth VScode, you might experience a snap issue due to the ENVIRONMENT VARIABLES. You can unset it as such:

unset GTK_PATH

```


**Running dev**

```
make dev
```

**Building**

```
make litbeat

```
