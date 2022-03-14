# MinesweeperSfml
Упрощённый клон игры Minesweeper.

В случае поражения нажмите R для перезапуска игры или N, чтобы начать новую игру.

Победой считается поле, на котором открыты все ячейки без мин, а ячейки с минами помечены "флажком". Если данные условия будут выполнены, запуститься новая игра.
[![Screenshot](https://raw.githubusercontent.com/Kkamikadzee/MinesweeperSfml/dev/.git_images/MinesweeperScreenshot.png "Screenshot")](https://raw.githubusercontent.com/Kkamikadzee/MinesweeperSfml/dev/.git_images/MinesweeperScreenshot.png "Screenshot")

------------
## Управление
- R - перезапустить игру;
- N - новая игра;
- ЛКМ - открыть ячейку;
- ПКМ - поменить ячейку или снять метку, если она уже стоит.

------------
## Запуск игры
При запуске игры можно передать следующие параметры:
```bash
-h [ --help ] # Подсказка
--window-width # Ширина окна с игрой
--window-height # Высота окна с игрой
--field-width # Количество ячеек в строке
--field-height # Количество ячеек в столбце
-n [ --number-mines ] # Количество мин на поле
```
