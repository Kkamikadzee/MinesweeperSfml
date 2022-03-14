#include <time.h>
#include <iostream>
#include <boost/program_options.hpp>
#include "Game.h"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    unsigned int windowWidth = 800, windowHeight = 600, fieldWidth = 10, fieldHeight = 10, numberMines = 10;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Help")
        ("window-width", po::value<unsigned int>(), "Set window width")
        ("window-height", po::value<unsigned int>(), "Set window height")
        ("field-width", po::value<unsigned int>(), "Set number cell in row")
        ("field-height", po::value<unsigned int>(), "Set number cell in column")
        ("number-mines,n", po::value<unsigned int>(), "Set number of mines")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("window-width"))
    {
        windowWidth = vm["window-width"].as<unsigned int>();
    }

    if (vm.count("window-height"))
    {
        windowHeight = vm["window-height"].as<unsigned int>();
    }

    if (vm.count("field-width"))
    {
        fieldWidth = vm["field-width"].as<unsigned int>();
    }

    if (vm.count("field-height"))
    {
        fieldHeight = vm["field-height"].as<unsigned int>();
    }

    if (vm.count("number-mines"))
    {
        numberMines = vm["number-mines"].as<unsigned int>();
    }

    srand(time(0));

    Kmk::Minesweeper::Game game(windowWidth, windowHeight, fieldWidth, fieldHeight, numberMines);

    game.Init();

    while (game.IsPlaying())
    {
        game.Update();
    }

    return 0;
}