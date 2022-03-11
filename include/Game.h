#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

namespace Kmk
{
    namespace Minesweeper
    {
        using FieldSizeType = unsigned int;
        using FieldCellType = unsigned char;
        class Game
        {
        public:
            Game(const unsigned int windowWidth, const unsigned int windowHeight,
                 const FieldSizeType fieldWidth, const FieldSizeType fieldHeight,
                 const unsigned int numberMines);

            Game(Game &orig) = delete;

            ~Game();

            Game operator=(Game &orig) = delete;

            void Init();
            void Update();
            inline const bool IsOpen()
            {
                return _window.isOpen();
            }

        private:
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

            static const std::string _pathToTiles;
            static const int _tileSideSize;

            static const std::string _gameName;

            unsigned int _windowWidth, _windowHeight;
            float _cellScale;
            float _cellPixelSize;
            sf::Vector2f _windowCenter;
            sf::Vector2f _positionLeftTopCell;
            sf::RenderWindow _window;

            FieldSizeType _fieldWidth, _fieldHeight;
            std::vector<FieldValue> _fieldGrid;
            std::vector<FieldValue> _viewFieldGrid;

            unsigned int _numberMines;

            bool _isEndGame;

            sf::Texture *_tilesTexture;
            sf::Sprite *_tilesSprite;

            template <typename T>
            T &GetCellFromVectorLike2dArray(std::vector<T> &v, const std::size_t x, const std::size_t y);

            const std::vector<std::pair<std::size_t, std::size_t>> GetNeighborsIndexes(const std::size_t xIndex, const std::size_t yIndex);

            void FillFieldGrid();

            void ResizeWindow(const unsigned int _windowWidth, const unsigned int _windowHeight);

            void DrawField();

            const bool IsCellSelected(const sf::Vector2i &mousePos);
            const std::pair<size_t, size_t> GetSelectedCell(const sf::Vector2i &mousePos);

            void OpenFieldCellHelper(FieldValue &fieldGridCell, FieldValue &viewGridCell);
            void OpenFieldCell(const std::size_t xIndex, const std::size_t yIndex);
            void OpenFieldCellCascade(const std::size_t xIndex, const std::size_t yIndex);

            void MarkMine(const std::size_t xIndex, const std::size_t yIndex);
        };
    } // namespace Minesweeper

} // namespace Kmk