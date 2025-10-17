finaL
win condition level when all levels completed
portal moves character to next level  
3-5 levels to design 














polish:
different blocks green
different background, orange png?
add dark blocks around outside. or just the collsion blocks?
knight turns direction you move








todo:
align sprite to collision box better to touch ground
blocks collide now, need to add spikes that kill player. enemy collision box to spike.
walking sprite animation
make sprite turn during the character moving. turns backgrounds in direction knight is walking.
block








polish:
- quirk with jumping spacebar does it more than once.s
- knight flowing cape when he's falling.


scale background correctly play state and death screen
knight jumping during jump
tile map editor











frame counter

Nice work getting the core mechanics down! Here's a solid roadmap for your platformer:

## Immediate Next Steps (Pick What Sounds Fun)

**1. Sprite Animations**
- Free sprite sources:
  - **itch.io** - Search "free platformer sprites" (tons of pixel art)
  - **OpenGameArt.org** - Good quality, properly licensed
  - **Kenney.nl** - Clean, consistent art style (highly recommended!)
  - Specific recommendation: **Kenney's "Platformer Pack"** - has characters, enemies, tiles, everything

**2. More Obstacles/Enemies**
- [ ] Add spike obstacles (static, instant death)
- [ ] Moving enemy (patrol back and forth)
- [ ] Jumping enemy
- [ ] Falling platforms
- [ ] Moving platforms you can ride

**3. Level Design**
- [ ] Create multiple platform heights (not just ground)
- [ ] Add collectibles (coins, stars)
- [ ] Goal/flag to reach end of level
- [ ] Multiple levels (load different enemy/platform positions)

**4. Polish Features**
- [ ] Camera follow player (when level is bigger than screen)
- [ ] Particle effects on death
- [ ] Screen shake on death
- [ ] Health system (3 lives before death screen)
- [ ] Timer/score counter

**5. Tile-Based Level (Big Step)**
- [ ] Create 2D array for level layout
- [ ] Load levels from text file
- [ ] Simple tile editor (click to place/remove tiles)

## Suggested Order
1. **Add spike obstacles** (easy win, reuse collision code)
2. **Get sprite sheet working** (visual upgrade feels great)
3. **Add moving enemy** (more challenge)
4. **Multiple platforms** (actual platforming!)
5. **Level goal + next level** (feels like a real game)

Take a break and come back fresh! 🎮














this worked:

~/Downloads/g0ridev.github.io/storage/platform-game $ ls
game.cpp     libraylib.a  notes.md     raylib.h
~/Downloads/g0ridev.github.io/storage/platform-game $ gcc -o game.exe game.cpp libraylib.a -lopengl32 -lgdi32 -lwinmm
~/Downloads/g0ridev.github.io/storage/platform-game $ ./game




Get a basic window running with Raylib first - just a colored background
Draw a simple rectangle that represents your player character
Make that rectangle move left/right with keyboard input
Add gravity - make it fall down constantly
Add a ground collision - stop falling when it hits the bottom