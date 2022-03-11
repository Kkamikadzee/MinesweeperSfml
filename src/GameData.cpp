#include <stdexcept>
#include <vector>
#include "GameData.h"

namespace Kmk
{
    namespace Minesweeper
    {

        GameData::GameData(const FieldSizeType fieldWidth, const FieldSizeType fieldHeight, const unsigned int numberMines)
            : FieldWidth(fieldWidth), FieldHeight(fieldHeight),
              _fieldGrid(), _viewFieldGrid(),
              NumberMines(numberMines),
              _numberOpenedCells(0), _numberMarkedMines(0),
              _isWin(false), _isDefeat(false)
        {
            if (NumberMines >= FieldWidth * FieldHeight)
            {
                throw std::runtime_error("Number of cells is less or equals than number of mines.");
            }

            for (auto heightCounter = 0; heightCounter < fieldHeight; ++heightCounter)
            {
                _fieldGrid.emplace_back();
                _viewFieldGrid.emplace_back();
                for (auto widthCounter = 0; widthCounter < fieldWidth; ++widthCounter)
                {
                    _fieldGrid[heightCounter].emplace_back();
                    _viewFieldGrid[heightCounter].emplace_back();
                }
            }
        }
    } // namespace Minesweeper
} // namespace Kmk