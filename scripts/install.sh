echo --------------------- INSTALL ---------------------

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
