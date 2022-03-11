#include <algorithm>
#include <vector>
#include <utility>
#include "GameData.h"
#include "GameLogic.h"

namespace Kmk
{
    namespace Minesweeper
    {
        GameLogic::GameLogic(GameData &gameData) : _gameData(gameData)
        {
        }

        void GameLogic::Start()
        {
            Restart();
            FillFieldGrid();
        }

        void GameLogic::Restart()
        {
            _gameData.SetWin(false);
            _gameData.SetDefeat(false);
            _gameData.SetNumberMarkedMines(0);
            _gameData.SetNumberOpenedCells(0);

            for (auto widthCounter = 0; widthCounter < _gameData.FieldWidth; ++widthCounter)
            {
                for (auto heightCounter = 0; heightCounter < _gameData.FieldHeight; ++heightCounter)
                {
                    _gameData.SetViewFieldGridCell(widthCounter, heightCounter, FieldValue::ClosedCell);
                }
            }
        }

        void GameLogic::OpenFieldCell(const std::size_t x, const std::size_t y)
        {
            auto cellValue = _gameData.GetFieldGridCell(x, y);

            OpenFieldCellHelper(x, y);

            if (cellValue == FieldValue::ZeroMinesNearby)
            {
                OpenFieldCellCascade(x, y);
            }
        }

        void GameLogic::MarkMine(const std::size_t x, const std::size_t y)
        {
            FieldValue cellValue = _gameData.GetViewFieldGridCell(x, y);
            switch (cellValue)
            {
            case FieldValue::ClosedCell:
            {
                _gameData.SetViewFieldGridCell(x, y, FieldValue::MarkedMine);
                _gameData.SetNumberMarkedMines(_gameData.GetNumberMarkedMines() + 1);
            }
            break;
            case FieldValue::MarkedMine:
            {
                _gameData.SetViewFieldGridCell(x, y, FieldValue::ClosedCell);
                _gameData.SetNumberMarkedMines(_gameData.GetNumberMarkedMines() - 1);
            }
            break;
            default:
                break;
            }

            CheckWin();
        }

        const std::vector<std::pair<std::size_t, std::size_t>> GameLogic::GetNeighborsIndexes(const std::size_t x, const std::size_t y)
        {
            std::vector<std::pair<std::size_t, std::size_t>> result;

            for (auto xNeighborOffset = -1; xNeighborOffset < 2; ++xNeighborOffset)
            {
                for (auto yNeighborOffset = -1; yNeighborOffset < 2; ++yNeighborOffset)
                {
                    if (yNeighborOffset == 0 && xNeighborOffset == 0)
                        continue;

                    int yNeighbor = y + yNeighborOffset, xNeighbor = x + xNeighborOffset;
                    if (yNeighbor < 0 || xNeighbor < 0 || yNeighbor >= _gameData.FieldHeight || xNeighbor >= _gameData.FieldWidth)
                        continue;

                    result.push_back(std::make_pair(xNeighbor, yNeighbor));
                }
            }
            return result;
        }

        void GameLogic::FillFieldGrid()
        {
            std::vector<FieldValue> fieldGridContent;
            for (auto counter = 0; counter < _gameData.FieldHeight * _gameData.FieldWidth; ++counter)
            {
                auto cellValue = counter < _gameData.NumberMines ? FieldValue::Mine : FieldValue::ZeroMinesNearby;
                fieldGridContent.emplace_back(cellValue);
            }

            std::random_shuffle(fieldGridContent.begin(), fieldGridContent.end());

            for (auto heightCounter = 0; heightCounter < _gameData.FieldHeight; ++heightCounter)
            {
                for (auto widthCounter = 0; widthCounter < _gameData.FieldWidth; ++widthCounter)
                {
                    _gameData.SetFieldGridCell(widthCounter, heightCounter, fieldGridContent[(heightCounter * _gameData.FieldWidth) + widthCounter]);
                    _gameData.SetViewFieldGridCell(widthCounter, heightCounter, FieldValue::ClosedCell);
                }
            }

            for (auto widthCounter = 0; widthCounter < _gameData.FieldWidth; ++widthCounter)
            {
                for (auto heightCounter = 0; heightCounter < _gameData.FieldHeight; ++heightCounter)
                {
                    if (_gameData.GetFieldGridCell(widthCounter, heightCounter) == FieldValue::Mine)
                    {
                        continue;
                    }

                    unsigned int neighborsCounter = 0;
                    auto neighborsIndexes = GetNeighborsIndexes(widthCounter, heightCounter);
                    for (auto neighborPtr = neighborsIndexes.begin(); neighborPtr != neighborsIndexes.end(); ++neighborPtr)
                    {
                        if (_gameData.GetFieldGridCell(neighborPtr->first, neighborPtr->second) == FieldValue::Mine)
                            ++neighborsCounter;
                    }

                    _gameData.SetFieldGridCell(widthCounter, heightCounter, static_cast<FieldValue>(neighborsCounter));
                }
            }
        }

        void GameLogic::OpenFieldCellHelper(const std::size_t x, const std::size_t y)
        {
            auto fieldCellValue = _gameData.GetFieldGridCell(x, y);
            _gameData.SetViewFieldGridCell(x, y, fieldCellValue);

            if (fieldCellValue == FieldValue::Mine)
            {
                Defeat();
            }

            _gameData.SetNumberOpenedCells(_gameData.GetNumberOpenedCells() + 1);

            CheckWin();
        }

        void GameLogic::OpenFieldCellCascade(const std::size_t x, const std::size_t y)
        {
            auto neighborsIndexes = GetNeighborsIndexes(x, y);
            for (auto neighborPtr = neighborsIndexes.begin(); neighborPtr != neighborsIndexes.end(); ++neighborPtr)
            {
                FieldValue fieldGridCell = _gameData.GetFieldGridCell(neighborPtr->first, neighborPtr->second),
                           viewGridCell = _gameData.GetViewFieldGridCell(neighborPtr->first, neighborPtr->second);
                if ((viewGridCell == FieldValue::ClosedCell) && (fieldGridCell != FieldValue::Mine))
                {
                    OpenFieldCellHelper(neighborPtr->first, neighborPtr->second);
                    if (fieldGridCell == FieldValue::ZeroMinesNearby)
                    {
                        OpenFieldCellCascade(neighborPtr->first, neighborPtr->second);
                    }
                }
            }
        }

        void GameLogic::CheckWin()
        {
            if (_gameData.NumberMines != _gameData.GetNumberMarkedMines())
            {
                return;
            }

            if (_gameData.NumberMines == (_gameData.FieldHeight * _gameData.FieldWidth) - _gameData.GetNumberOpenedCells())
            {
                _gameData.SetWin(true);
            }
        }

        void GameLogic::Defeat()
        {
            for (auto widthCounter = 0; widthCounter < _gameData.FieldWidth; ++widthCounter)
            {
                for (auto heightCounter = 0; heightCounter < _gameData.FieldHeight; ++heightCounter)
                {
                    auto fieldCellValue = _gameData.GetFieldGridCell(widthCounter, heightCounter),
                         viewFieldCellValue = _gameData.GetViewFieldGridCell(widthCounter, heightCounter);

                    if (fieldCellValue == FieldValue::Mine && viewFieldCellValue == FieldValue::MarkedMine)
                    {
                        continue;
                    }

                    _gameData.SetViewFieldGridCell(widthCounter, heightCounter, fieldCellValue);
                }
            }

            _gameData.SetDefeat(true);
        }
    } // namespace Minesweeper
} // namespace Kmk