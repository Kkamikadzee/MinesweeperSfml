#include <exception>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

namespace Kmk
{
    namespace Minesweeper
    {
        // TODO: Убрать абсолютный путь
        const std::string Game::_pathToTiles = "C:/Source/C++/MinesweeperSfml/assets/tiles.jpg";
        const int Game::_tileSideSize = 32;

        const std::string Game::_gameName = "Minesweeper";

        Game::Game(const unsigned int windowWidth, const unsigned int windowHeight,
                   const FieldSizeType fieldWidth, const FieldSizeType fieldHeight,
                   const unsigned int numberMines)
            : _windowWidth(windowWidth), _windowHeight(windowHeight),
              _fieldWidth(fieldWidth), _fieldHeight(fieldHeight),
              _fieldGrid(), _viewFieldGrid(),
              _numberMines(numberMines), _isEndGame(false),
              _window()
        {
            ResizeWindow(_windowWidth, _windowHeight);
        }

        Game::~Game()
        {
            delete _tilesSprite;
            delete _tilesTexture;
        }

        void Game::Init()
        {
            _window.create(sf::VideoMode(_windowWidth, _windowHeight), Game::_gameName);
            _tilesTexture = new sf::Texture;
            _tilesTexture->loadFromFile(Game::_pathToTiles);
            _tilesSprite = new sf::Sprite(*_tilesTexture);

            FillFieldGrid();
        }

        void Game::Update()
        {
            for (sf::Event event; _window.pollEvent(event); /* */)
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    _window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(_window);
                    if (IsCellSelected(pos))
                    {
                        auto selectedCell = GetSelectedCell(pos);
                        if (event.key.code == sf::Mouse::Left)
                        {
                            OpenFieldCell(selectedCell.first, selectedCell.second);
                        }
                        else if (event.key.code == sf::Mouse::Right)
                        {
                            MarkMine(selectedCell.first, selectedCell.second);
                        }
                    }
                }
                break;
                case sf::Event::Resized:
                    ResizeWindow(event.size.width, event.size.height);
                    break;
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::R:
                    {
                        // TODO: Перезапуск игры
                        _window.close();
                        _fieldGrid.clear();
                        _viewFieldGrid.clear();
                        _isEndGame = false;
                        delete _tilesSprite;
                        delete _tilesTexture;
                        Init();
                    }
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

            DrawField();
        }

        template <typename T>
        inline T &Game::GetCellFromVectorLike2dArray(std::vector<T> &v, const std::size_t x, const std::size_t y)
        {
            return v[(_fieldWidth * y) + x];
        }

        const std::vector<std::pair<std::size_t, std::size_t>> Game::GetNeighborsIndexes(const std::size_t xIndex, const std::size_t yIndex)
        {
            std::vector<std::pair<std::size_t, std::size_t>> result;

            for (auto yIndexNeighborOffset = -1; yIndexNeighborOffset < 2; ++yIndexNeighborOffset)
            {
                for (auto xIndexNeighborOffset = -1; xIndexNeighborOffset < 2; ++xIndexNeighborOffset)
                {
                    if (yIndexNeighborOffset == 0 && xIndexNeighborOffset == 0)
                        continue;

                    int yIndexNeighbor = yIndex + yIndexNeighborOffset, xIndexNeighbor = xIndex + xIndexNeighborOffset;
                    if (yIndexNeighbor < 0 || xIndexNeighbor < 0 || yIndexNeighbor >= _fieldHeight || xIndexNeighbor >= _fieldWidth)
                        continue;

                    result.push_back(std::make_pair(xIndexNeighbor, yIndexNeighbor));
                }
            }
            return result;
        }

        void Game::FillFieldGrid()
        {
            for (auto counter = 0; counter < _fieldWidth * _fieldHeight; ++counter)
            {
                _fieldGrid.emplace_back(FieldValue::ZeroMinesNearby);
                _viewFieldGrid.emplace_back(FieldValue::ClosedCell);
            }

            if (_numberMines >= _fieldWidth * _fieldHeight)
            {
                throw std::runtime_error("Number of cells is less or equals than number of mines.");
            }

            unsigned int numberPlacedMines = 0;
            for (auto cellPtr = _fieldGrid.begin();
                 numberPlacedMines < _numberMines && cellPtr != _fieldGrid.end();
                 ++cellPtr, ++numberPlacedMines)
            {
                *cellPtr = FieldValue::Mine;
            }

            std::random_shuffle(_fieldGrid.begin(), _fieldGrid.end());

            for (auto yIndex = 0; yIndex < _fieldHeight; ++yIndex)
            {
                for (auto xIndex = 0; xIndex < _fieldWidth; ++xIndex)
                {
                    if (GetCellFromVectorLike2dArray(_fieldGrid, xIndex, yIndex) == FieldValue::Mine)
                        continue;

                    int counter = 0;
                    auto neighborsIndexes = GetNeighborsIndexes(xIndex, yIndex);
                    for (auto neighborPtr = neighborsIndexes.begin(); neighborPtr != neighborsIndexes.end(); ++neighborPtr)
                    {
                        if (GetCellFromVectorLike2dArray(_fieldGrid, neighborPtr->first, neighborPtr->second) == FieldValue::Mine)
                            ++counter;
                    }

                    GetCellFromVectorLike2dArray(_fieldGrid, xIndex, yIndex) = static_cast<FieldValue>(counter);
                }
            }
        }

        void Game::ResizeWindow(const unsigned int windowWidth, const unsigned int windowHeight)
        {
            _windowWidth = windowWidth;
            _windowHeight = windowHeight;
            _windowCenter = sf::Vector2f(windowWidth, windowHeight) / 2.0f;

            _cellScale = std::min(static_cast<float>(windowWidth) / _fieldWidth / Game::_tileSideSize, static_cast<float>(windowHeight) / _fieldHeight / Game::_tileSideSize);

            _cellPixelSize = Game::_tileSideSize * _cellScale;

            _positionLeftTopCell = _windowCenter - (sf::Vector2f(_fieldWidth, _fieldHeight) * _cellPixelSize / 2.0f);

            _window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight))));
        }

        inline const bool Game::IsCellSelected(const sf::Vector2i &mousePos)
        {
            auto rightBottomCornerField = _windowCenter + _positionLeftTopCell;
            return ((mousePos.x >= _positionLeftTopCell.x) && (mousePos.y >= _positionLeftTopCell.y)) ||
                   ((mousePos.x <= rightBottomCornerField.x) && (mousePos.y <= rightBottomCornerField.y));
        }

        inline const std::pair<size_t, size_t> Game::GetSelectedCell(const sf::Vector2i &mousePos)
        {
            int x = (mousePos.x - _positionLeftTopCell.x) / (Game::_tileSideSize * _cellScale);
            int y = (mousePos.y - _positionLeftTopCell.y) / (Game::_tileSideSize * _cellScale);

            return std::make_pair(x, y);
        }

        void Game::DrawField()
        {
            _window.clear(sf::Color::White);

            for (int yIndex = 0; yIndex < _fieldHeight; ++yIndex)
            {
                for (int xIndex = 0; xIndex < _fieldWidth; ++xIndex)
                {
                    // TODO: Кусок игровой логики
                    if (_isEndGame)
                    {
                        GetCellFromVectorLike2dArray(_viewFieldGrid, xIndex, yIndex) = GetCellFromVectorLike2dArray(_fieldGrid, xIndex, yIndex);
                    }

                    _tilesSprite->setTextureRect(
                        sf::IntRect(static_cast<FieldCellType>(GetCellFromVectorLike2dArray(_viewFieldGrid, xIndex, yIndex)) * Game::_tileSideSize,
                                    0,
                                    Game::_tileSideSize,
                                    Game::_tileSideSize));

                    _tilesSprite->setScale(_cellScale, _cellScale);

                    _tilesSprite->setPosition(_positionLeftTopCell + sf::Vector2f(xIndex * _cellPixelSize, yIndex * _cellPixelSize));

                    _window.draw(*_tilesSprite);
                }
            }

            _window.display();
        }

        inline void Game::OpenFieldCellHelper(FieldValue &fieldGridCell, FieldValue &viewGridCell)
        {
            viewGridCell = fieldGridCell;
        }

        void Game::OpenFieldCell(const std::size_t xIndex, const std::size_t yIndex)
        {
            auto cellValue = GetCellFromVectorLike2dArray(_fieldGrid, xIndex, yIndex);

            if (cellValue == FieldValue::Mine)
                _isEndGame = true;

            OpenFieldCellHelper(cellValue, GetCellFromVectorLike2dArray(_viewFieldGrid, xIndex, yIndex));

            if (cellValue == FieldValue::ZeroMinesNearby)
            {
                OpenFieldCellCascade(xIndex, yIndex);
            }
        }

        void Game::OpenFieldCellCascade(const std::size_t xIndex, const std::size_t yIndex)
        {
            auto neighborsIndexes = GetNeighborsIndexes(xIndex, yIndex);
            for (auto neighborPtr = neighborsIndexes.begin(); neighborPtr != neighborsIndexes.end(); ++neighborPtr)
            {
                FieldValue &fieldGridCell = GetCellFromVectorLike2dArray(_fieldGrid, neighborPtr->first, neighborPtr->second),
                           &viewGridCell = GetCellFromVectorLike2dArray(_viewFieldGrid, neighborPtr->first, neighborPtr->second);
                if ((viewGridCell == FieldValue::ClosedCell) && (fieldGridCell != FieldValue::Mine))
                {
                    OpenFieldCellHelper(fieldGridCell, viewGridCell);
                    if (fieldGridCell == FieldValue::ZeroMinesNearby)
                    {
                        OpenFieldCellCascade(neighborPtr->first, neighborPtr->second);
                    }
                }
            }
        }

        void Game::MarkMine(const std::size_t xIndex, const std::size_t yIndex)
        {
            FieldValue &cell = GetCellFromVectorLike2dArray(_viewFieldGrid, xIndex, yIndex);
            switch (cell)
            {
            case FieldValue::ClosedCell:
                cell = FieldValue::MarkedMine;
                break;
            case FieldValue::MarkedMine:
                cell = FieldValue::ClosedCell;
                break;
            default:
                break;
            }
        }
    } // namespace Minesweeper

} // namespace Kmk