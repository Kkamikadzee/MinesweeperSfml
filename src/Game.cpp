#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Kmk
{
    namespace Minesweeper
    {
        Game::Game(const unsigned int windowWidth, const unsigned int windowHeight,
                   const FieldSizeType fieldWidth, const FieldSizeType fieldHeight,
                   const unsigned int numberMines)
            : _gameData(fieldWidth, fieldHeight, numberMines),
              _gameLogic(_gameData),
              _gameView(windowWidth, windowHeight, _gameData),
              _isPlaying(false)
        {
        }

        void Game::Init()
        {
            _gameLogic.Start();
            _gameView.Init();
            _isPlaying = true;
        }

        void Game::Update()
        {
            for (sf::Event event; _gameView.PollEvent(event); /* */)
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    _isPlaying = false;
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i pos(event.mouseButton.x, event.mouseButton.y);
                    if (_gameView.IsCellSelected(pos))
                    {
                        auto selectedCell = _gameView.GetSelectedCell(pos);
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            _gameLogic.OpenFieldCell(selectedCell.first, selectedCell.second);
                        }
                        else if (event.mouseButton.button == sf::Mouse::Right)
                        {
                            _gameLogic.MarkMine(selectedCell.first, selectedCell.second);
                        }
                    }
                }
                break;
                case sf::Event::Resized:
                    _gameView.ResizeWindow(event.size.width, event.size.height);
                    break;
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::R:
                        _gameLogic.Restart();
                        break;
                    case sf::Keyboard::N:
                        _gameLogic.Start();
                        break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
            }

            if (_gameData.IsWin())
            {
                _gameLogic.Start();
            }

            _gameView.DrawField();
        }
    } // namespace Minesweeper

} // namespace Kmk