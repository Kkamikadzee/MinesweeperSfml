#pragma once
#include "GameData.h"
#include "GameLogic.h"
#include "GameView.h"

namespace Kmk
{
    namespace Minesweeper
    {
        class Game
        {
        public:
            Game(const unsigned int windowWidth, const unsigned int windowHeight,
                 const FieldSizeType fieldWidth, const FieldSizeType fieldHeight,
                 const unsigned int numberMines);

            Game(Game &orig) = delete;
            Game operator=(Game &orig) = delete;

            void Init();
            void Update();
            inline const bool IsPlaying()
            {
                return _isPlaying;
            }

        private:
            bool _isPlaying;

            GameData _gameData;
            GameLogic _gameLogic;
            GameView _gameView;
        };
    } // namespace Minesweeper
} // namespace Kmk