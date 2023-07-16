echo --------------------- INSTALL ---------------------

echo ------- INSTALL BASIC LIBS -------
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt-get install unzip

echo ------- INSTALL DEP. FOR TGLIB ------- 

sudo apt-get install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev

echo ------- INSTALL TGLIB ------- 

git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
cd ..
rm -rf tgbot-cpp


echo ------- INSTALL PQXX ------- 

git clone https://github.com/jtv/libpqxx.git
cd libpqxx
./configure
make -j4
sudo make install
cd ..
rm -rf libpqxx

echo ------- INSTALL QT ------- 
sudo apt-get install qtcreator

git clone https://github.com/qt/qtbase/
cd qtbase
mkdir build && cd build 
cmake ..
make -j4
sudo make install
cd ../.. && rm -rf qtbase

sudo apt get install qt6-tools-dev qt6-l10n-tools

