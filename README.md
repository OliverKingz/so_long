# so_long  
[42 Cursus] A simple 2D game built with **MLX42** where the player must collect all items and reach the exit while navigating a custom map.  
This project was designed to enhance skills in **graphics programming**, **event handling**, and **C programming**.

![Example of so_long](assets/images/so_long_bonus.gif)

Keywords  
- **2D Game Development**  
- **Graphics Programming**  
- **MLX42**  
- **Tiles and Sprites**  
- **Map Parsing**  
- **Event Handling**  
- **Memory Management**  
- **Game Logic**  
- **Animation**  
- **C Programming**  

---

## Overview  
**so_long** is a small 2D game developed using the **MLX42** library. It introduces players to the basics of game development, including map navigation, item collection, and obstacle avoidance. The project emphasizes practical learning, offering hands-on experience with **graphics rendering**, **event handling**, and **resource management**. It’s a fun and accessible way to explore game mechanics and programming concepts.  

---

## Features  
- Navigate the map using **W, A, S, D** or **arrow keys**.  
- Collect items and reach the exit while avoiding obstacles.  
- Display the number of movements in the terminal after each action.  
- Simple graphics using **MLX42**.  
- Custom map parsing and validation.  
- Clean window management (ESC key and close button).  

### Bonus Features
- Movement Counter: A counter that displays the number of moves on the game window.
- Item Animation: Items are animated, using the loop hook.
- Player Animation: The player sprite animates when moving, using the key hook.
- Enemies + Animation: Animated Enemies are added to the map, using loop hook. 
- Exit Animation: when all collectibles are collected, the exit opens. 

---

## How to Play

1. Use the **arrow keys** or **WASD** to move the player.
2. Collect all the items (`C`) on the map to unlock the exit (`E`).
3. Reach the exit to win the game!
4. Avoid static enemies (`X`), as they block your path.

### Controls

- **W** / **Up Arrow**: Move up.
- **A** / **Left Arrow**: Move left.
- **S** / **Down Arrow**: Move down.
- **D** / **Right Arrow**: Move right.
- **ESC**: Quit the game.

---

## What I Learned  
This project was a great opportunity to deepen my understanding of:  
- **Graphics Programming**: Working with **MLX42** to render textures, handle window events, and manage animations.  
- **Game Logic**: Developed a solid understanding of game mechanics, including player movement, item collection, and win/lose conditions.  
- **Memory Management**: Ensuring proper allocation and deallocation of resources to avoid leaks.  
- **Map Parsing and Validation**: Implementing robust logic to validate map files and ensure they meet game requirements.  
- **Event Handling**: Managing keyboard inputs and window events for smooth gameplay.  
- **Resource Management**: Efficiently managing and animating game assets like sprites and tiles.  
- **Coordinate Management**: Handling 2D coordinates and implementing game logic based on grid-based systems.  
- **Creative Problem Solving**: Tackling challenges such as map validation, animation loops, and enemy behavior, which enhanced my ability to think critically and creatively.  

---

## Installation  
Requites **MLX42** library and its dependencies.  

### How to Run  
1. Clone this repository:  
   ```bash  
   git clone https://github.com/yourusername/so_long.git  
   cd so_long  
   ```  

2. Compile the project using the provided **Makefile**, use the bonus rule for a better experience:  
   ```bash  
   make bonus
   ```  

3. Run the game with a map file (e.g., `example.ber` for mandatory, `enemies.ber` for bonus):  
   ```bash  
   ./so_long assets/maps/example.ber
   ./so_long_bonus assets/maps/enemies.ber

   ```

---

### Error Handling  

| **Error Scenario**                                      | **Error Message**                                                                 |
|---------------------------------------------------------|-----------------------------------------------------------------------------------|
| **No map file provided**                                | `Error\nInvalid map: needs .ber extension`                                        |
| **Map file does not exist**                             | `Error\nInvalid map: unable to open or doesn't exists`                            |
| **Map file is empty**                                   | `Error\nInvalid map: file is empty`                                               |
| **Map file is too big (max 100x50)**                    | `Error\nInvalid map: too big, max 100x50`                                         |
| **Map file is not rectangular**                         | `Error\nInvalid map: not rectangular`                                             |
| **Map file cannot be opened**                           | `Error\nInvalid map: unable to open`                                              |
| **Map file contains invalid characters**                | `Error\nInvalid map: invalid char introduced`                                     |
| **Map has no collectibles**                             | `Error\nInvalid map: needs 1+ Collectibles`                                       |
| **Map has no exit**                                     | `Error\nInvalid map: needs 1x Exit only`                                          |
| **Map has no player starting position**                 | `Error\nInvalid map: needs 1x Player only`                                        |
| **Map has multiple exits or players**                   | `Error\nInvalid map: needs 1x Exit only` or `Error\nInvalid map: needs 1x Player only` |
| **Map is not enclosed by walls**                        | `Error\nInvalid map: needs enclosed in Walls (row check)` or `Error\nInvalid map: needs enclosed in Walls (column check)` |
| **Collectibles are unreachable**                        | `Error\nInvalid map: Collectibles aren't reachable`                               |
| **Exit is unreachable**                                 | `Error\nInvalid map: Exit is not reachable`                                       |
| **MLX42-specific errors**                               | `Error\nMLX42 Error: [specific MLX42 error message]`                              |

---

## Assets Credits  
The sprites and textures used in this project are a mix of **custom-made assets** and modified/copied assets from **[Sunnyside World by Daniel Diggle](https://danieldiggle.itch.io/sunnyside)**, available for free on itch.io.  
- **Custom Assets**: Some textures were created or modified by me to fit the game's theme.  
- **Sunnyside World**: The original sprites and textures were sourced from this fantastic resource.  
Thank you to the creator for making these assets available!  

---

## Author

- **Name**: Oliver King Zamora
- **GitHub**: [oliverkingz](https://github.com/oliverkingz)
- **42 Login**: ozamora-

---

## Acknowledgments  
This project is part of the **42 Cursus**, a rigorous programming curriculum that emphasizes hands-on learning and problem-solving. Special thanks to the 42 team for providing this challenging and rewarding project!  

--- 
