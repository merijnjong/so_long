# so_long
In this exercise I have to create a basic 2D game in which a dolphin escapes Earth after<br />
eating some fish. Instead of a dolphin, fish, and the Earth, I can use any character, any<br />
collectible and any place I want.
Program name | so_long |
|:--- |:---
Program name | so_long |
Turn in files | [Makefile](https://github.com/merijnjong/so_long/blob/main/Makefile), [so_long.h](https://github.com/merijnjong/so_long/blob/main/so_long.h), [so_long.c](https://github.com/merijnjong/so_long/blob/main/so_long.c), [so_long_check.c](https://github.com/merijnjong/so_long/blob/main/so_long_check.c), [so_long_display.c](https://github.com/merijnjong/so_long/blob/main/so_long_display.c),<br />[so_long_move.c](https://github.com/merijnjong/so_long/blob/main/so_long_move.c), [so_long_utils.c](https://github.com/merijnjong/so_long/blob/main/so_long_utils.c), [maps](https://github.com/merijnjong/so_long/tree/main/maps), [textures](https://github.com/merijnjong/so_long/tree/main/assets) |
Makefile | NAME, all, clean, fclean, re |
Arguments | A map in format *.ber |
External functions | • open, close, read, write, malloc, free, perror, strerror, exit<br />• All functions of the math library (-lm compiler option, man man 3 math)<br />• All functions of the MiniLibX<br />• ft_printf and any equivalent YOU coded |
Libft authorized | Yes |

### Instructions
Your project must comply with the following rules:
* You must use the MiniLibX. Either the version available on the school machines,
or installing it using its sources.
* You have to turn in a Makefile which will compile your source files. It must not
relink.
* Your program has to take as parameter a map description file ending with the .ber
extension.

### Game
* The player’s goal is to collect every collectible present on the map, then escape
chosing the shortest possible route.
* The W, A, S, and D keys must be used to move the main character.
* The player should be able to move in these 4 directions: up, down, left, right.
* The player should not be able to move into walls.
* At every move, the current number of movements must be displayed in the shell.
* You have to use a 2D view (top-down or profile).
* The game doesn’t have to be real time.
* Although the given examples show a dolphin theme, you can create the world you
want.

### Graphic Management
* Your program has to display the image in a window.
* The management of your window must remain smooth (changing to another win-
dow, minimizing, and so forth).
* Pressing ESC must close the window and quit the program in a clean way.
* Clicking on the cross on the window’s frame must close the window and quit the
program in a clean way.
* The use of the images of the MiniLibX is mandatory.

### Map
* The map has to be constructed with 3 components: walls, collectibles, and free
space.
* The map can be composed of only these 5 characters:<br />
  0 for an empty space,<br />
  1 for a wall,<br />
  C for a collectible,<br />
  E for a map exit,<br />
  P for the player's starting position.<br />
* The map must contain 1 exit, at least 1 collectible, and 1 starting position to
be valid.
* The map must be rectangular.
* The map must be closed/surrounded by walls. If it’s not, the program must return
an error.
* You have to check if there’s a valid path in the map.
* You must be able to parse any kind of map, as long as it respects the above rules.
* If any misconfiguration of any kind is encountered in the file, the program must
exit in a clean way, and return "Error\n" followed by an explicit error message of
your choice.
