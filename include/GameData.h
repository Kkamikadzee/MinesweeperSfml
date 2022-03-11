#pragma once
#include <vector>

namespace Kmk
{
    namespace Minesweeper
    {
        using FieldSizeType = std::size_t;
        using FieldCellType = unsigned char;

        enum class FieldValue : FieldCellType
        {
            ZeroMinesNearby = 0,
            OneMineNearby = 1,
            TwoMinesNearby = 2,
            ThreeMinesNearby = 3,
            FourMinesNearby = 4,
            FiveMinesNearby = 5,
            SixMinesNearby = 6,
            SevenMinesNearby = 7,
            EightMinesNearby = 8,
            Mine = 9,
            ClosedCell = 10,
            MarkedMine = 11
        };

        class GameData
        {
        public:
            const FieldSizeType FieldWidth, FieldHeight;

            const unsigned int NumberMines;

            GameData(const FieldSizeType fieldWidth, const FieldSizeType fieldHeight, const unsigned int numberMines);

            inline const FieldValue GetFieldGridCell(const FieldSizeType x, const FieldSizeType y) const
            {
                return _fieldGrid[y][x];
            }

            inline void SetFieldGridCell(const FieldSizeType x, const FieldSizeType y, const FieldValue value)
            {
                _fieldGrid[y][x] = value;
            }

            inline const FieldValue GetViewFieldGridCell(const FieldSizeType x, const FieldSizeType y) const
            {
                return _viewFieldGrid[y][x];
            }

            inline void SetViewFieldGridCell(const FieldSizeType x, const FieldSizeType y, const FieldValue value)
            {
                _viewFieldGrid[y][x] = value;
            }

            inline const unsigned int GetNumberOpenedCells() const
            {
                return _numberOpenedCells;
            }

            inline void SetNumberOpenedCells(const unsigned int value)
            {
                _numberOpenedCells = value;
            }

            inline const unsigned int GetNumberMarkedMines() const
            {
                return _numberMarkedMines;
            }

            inline void SetNumberMarkedMines(const unsigned int value)
            {
                _numberMarkedMines = value;
            }

            inline const bool IsWin() const
            {
                return _isWin;
            }

            inline void SetWin(const bool value)
            {
                _isWin = value;
            }

            inline const bool IsDefeat() const
            {
                return _isDefeat;
            }

            inline void SetDefeat(const bool value)
            {
                _isDefeat = value;
            }

        private:
            unsigned int _numberOpenedCells;
            unsigned int _numberMarkedMines;

            bool _isWin;
            bool _isDefeat;

            std::vector<std::vector<FieldValue>> _fieldGrid;
            std::vector<std::vector<FieldValue>> _viewFieldGrid;
        };
    } // namespace Minesweeper
} // namespace Kmk