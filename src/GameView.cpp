#include <algorithm>
#include <utility>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "GameView.h"

namespace Kmk
{
    namespace Minesweeper
    {
        const std::string GameView::_pathToTiles = "assets/tiles.jpg";
        const int GameView::_tileSideSize = 32;

        const std::string GameView::_gameName = "Minesweeper";

        GameView::GameView(const unsigned int windowWidth, const unsigned int windowHeight, GameData &gameData)
            : _windowWidth(0), _windowHeight(0),
              _gameData(gameData),
              _window(), _tilesTexture(), _tilesSprite()
        {
            ResizeWindow(windowWidth, windowHeight);
        }

        GameView::~GameView()
        {
            _window.close();
        }

        void GameView::Init()
        {
            _window.create(sf::VideoMode(_windowWidth, _windowHeight), GameView::_gameName);
            _tilesTexture.loadFromFile(GameView::_pathToTiles);
            _tilesSprite.setTexture(_tilesTexture);
        }

        const bool GameView::PollEvent(sf::Event &event)
        {
            return _window.pollEvent(event);
        }

        void GameView::ResizeWindow(const unsigned int windowWidth, const unsigned int windowHeight)
        {
            _windowWidth = windowWidth;
            _windowHeight = windowHeight;
            _windowCenter = sf::Vector2f(windowWidth, windowHeight) / 2.0f;

            _cellScale = std::min(static_cast<float>(windowWidth) / _gameData.FieldWidth / GameView::_tileSideSize,
                                  static_cast<float>(windowHeight) / _gameData.FieldHeight / GameView::_tileSideSize);

            _cellPixelSize = GameView::_tileSideSize * _cellScale;

            _positionLeftTopCell = _windowCenter - (sf::Vector2f(_gameData.FieldWidth, _gameData.FieldHeight) * _cellPixelSize / 2.0f);

            _window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight))));
        }

        void GameView::DrawField()
        {
            _window.clear(sf::Color::White);

            for (int yIndex = 0; yIndex < _gameData.FieldHeight; ++yIndex)
            {
                for (int xIndex = 0; xIndex < _gameData.FieldWidth; ++xIndex)
                {
                    _tilesSprite.setTextureRect(
                        sf::IntRect(static_cast<FieldCellType>(_gameData.GetViewFieldGridCell(xIndex, yIndex)) * GameView::_tileSideSize,
                                    0,
                                    GameView::_tileSideSize,
                                    GameView::_tileSideSize));

                    _tilesSprite.setScale(_cellScale, _cellScale);

                    _tilesSprite.setPosition(_positionLeftTopCell + sf::Vector2f(xIndex * _cellPixelSize, yIndex * _cellPixelSize));

                    _window.draw(_tilesSprite);
                }
            }

            _window.display();
        }
    } // namespace Minesweeper
} // namespace Kmk