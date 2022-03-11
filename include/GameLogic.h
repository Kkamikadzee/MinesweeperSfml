#pragma once
#include <vector>
#include <utility>
#include "GameData.h"

namespace Kmk
{
    namespace Minesweeper
    {
        class GameLogic
        {
        public:
            GameLogic(GameData &gameData);

            void Start();

            void Restart();

            void OpenFieldCell(const std::size_t x, const std::size_t y);

            void MarkMine(const std::size_t x, const std::size_t y);

        private:
            GameData &_gameData;

            const std::vector<std::pair<std::size_t, std::size_t>> GetNeighborsIndexes(const std::size_t x, const std::size_t y);

            void FillFieldGrid();

            void OpenFieldCellHelper(const std::size_t x, const std::size_t y);
            void OpenFieldCellCascade(const std::size_t x, const std::size_t y);

            void Defeat();

            void CheckWin();
        };
    } // namespace Minesweeper
} // namespace Kmk