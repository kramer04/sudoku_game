# sudoku_game
Play to sudoku 9x9

To compile on Ubuntu 22.04 :
https://terminalroot.com/how-to-install-gtkmm-4-on-ubuntu-2204/

g++ main.cpp src/*.cpp -std=c++20 -I include -o sudoku \`pkg-config gtkmm-4.0 --cflags --libs cairomm-1.16\` -Wall -Wextra -O2
