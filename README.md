## Game specifications

In its final state, this game must meet the following requirements. 

1. Assets:
- Here, the Textures and Animations that will be used to render entities along with the Fonts are going to be denoted as "Assets".
- Assets are loaded once at the beginning of the program and stored in the Assets class, which is stored by the GameEngine class.
- All Assets are defined in a specific file, with the syntax defined below.

2. Note:
- All entity positions denote the center of their rectangular sprite. It also denotes the center or the bounding box, if it has one.

3. Player:
- The player Entity in the game is represented by Garfield, which has several different Animation: Stand, Run, and Air.
- The player moves with the following controls: \
Left: Q key, Right: D key, Jump Z key, Shoot Space key. This last is for an AZERY keyboard but the implementation should be done in order to have the same physical key for any keyboard configurations, for example "WASD" for an QWERTY keyboard. 
- The player can move left, move right, or shoot at any time during the game. This mean the player can move right/left or shoot while in the air.
- The player can onlu jump if it is currently standig on a tile.
- If the jump key is held, the player should not continously jump, but instead should only jump once per button pres. If the player lets go of the jump key mid-jump, it should stat falling back down immediately.
- Bullets shot by the player travel in the direction the player is facing
- The player collides with "Tile" entities in the level and can not move through them. The player land on a Tile entity and stand in place if it falls on it from above.
- The player does not collide with "Dec" entities in the level.
- If the player falls below the bottom of the screen, they respawn at the start.
- The player should have a Gravity component with constantly accelerates it downward on the screen until it collides with a tile.
- The player has a maximum speed specified in the Level file which it should not exceed in eiter x or y direction.
- The player will be given a CBoundingBox of a size specidied in the level file
- The player's sprite and bounding box are centered on the player's position.

4. Animations:
- Animations are implemented by storing multiple frames inside a texture
- Anamitions can be repeating or non-repeating.
- Any entity with a non-repeating animation should be destroyed once its Animation has ended.

