#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include "GameData.h"

namespace Kmk
{
    namespace Minesweeper
    {
        class GameView
        {
        public:
            GameView(const unsigned int windowWidth, const unsigned int windowHeight, GameData &gameData);

            ~GameView();

            void Init();

            const bool PollEvent(sf::Event &event);

            void ResizeWindow(const unsigned int windowWidth, const unsigned int windowHeight);

            void DrawField();

            inline const bool IsCellSelected(const sf::Vector2i &mousePos)
            {
                auto rightBottomCornerField = _windowCenter + _positionLeftTopCell;
                return ((mousePos.x >= _positionLeftTopCell.x) && (mousePos.y >= _positionLeftTopCell.y)) ||
                       ((mousePos.x <= rightBottomCornerField.x) && (mousePos.y <= rightBottomCornerField.y));
            }

            inline const std::pair<FieldSizeType, FieldSizeType> GetSelectedCell(const sf::Vector2i &mousePos)
            {
                int x = (mousePos.x - _positionLeftTopCell.x) / (GameView::_tileSideSize * _cellScale);
                int y = (mousePos.y - _positionLeftTopCell.y) / (GameView::_tileSideSize * _cellScale);

                return std::make_pair(x, y);
            }

        private:
            static const std::string _pathToTiles;
            static const int _tileSideSize;

            static const std::string _gameName;

            GameData &_gameData;

            unsigned int _windowWidth, _windowHeight;
            float _cellScale;
            float _cellPixelSize;
            sf::Vector2f _windowCenter;
            sf::Vector2f _positionLeftTopCell;
            sf::RenderWindow _window;

            sf::Texture _tilesTexture;
            sf::Sprite _tilesSprite;
        };
    } // namespace Minesweeper
} // namespace Kmk