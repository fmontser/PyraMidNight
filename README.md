# PyraMidNight
Work in progress!

A tribute to classic game Arkanoid!

Mimics a coin-up arcade machine.

Controls:
 - ESC: opens the menu, you can ajust volume levels here.
 - NUM1: insert coin!, only in title screen choose wisely 1 credit 1 ball.
 - A: bumper move left, cursor left.
 - D: bumer move right, cursor rigth.
 - W: cursor up, rotate character on ranking screen.
 - S: cursor down, rotate character on ranking screen.
 - RCTRL: hold for bumper fine control, slows down.
 - RSHIFT: hold for bumer coarse control, speeds up.
 - SPACE: launch ball, enter name on ranking screen.


 Features:
 - Classic arkanoid gameplay
 - Bumper hit position changes ball attack angle
 - Bumper fine and coarse control
 - Blocks with properties
 - Power ups, including, extra score, extra credit, magic misile
 - Ghost enemies
 - Render effects
 - Credit and score system
 - Score ranking
 - Multiple levels
 - Level editing posible (tilemap)
 - Audio! music and soud effects
 - Music and SFX volume controls
 - Persistency of user data (records, audio volume)



Level editing:

The file Levels.hpp contains editable levels, rules:
 - You can pass the number of level as executable argument to test the level directly
 - has to be 9x9 characters (9 strings). The game will validate at compile time and throw an exception.
 - add the level to ROUNDS vector just below.
 - edit the constexpr GAME_FINAL_ROUND_ID to math the last level index (4 levels = 3).
 - valid input is 0,1,2,3
