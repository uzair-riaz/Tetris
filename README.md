Due to this project's heavy reliance on the SDL library for graphics, it can easily be setup with the Code::Blocks IDE. However, it is not compatible with Dev-C++ as of yet.

Installation:

1. Install Code::Blocks IDE
2. Open "Tetris.cbp" in Code::Blocks
3. Right-click the "Tetris" project in the Projects bar on the left. Go to Build Options -> Search Directories -> Compiler, click Add, type "include" in the popup box and press OK
3. Right-click the "Tetris" project in the Projects bar on the left. Go to Build Options -> Search Directories -> Linker, click Add, type "lib" in the popup box and press OK
4. Right-click the "Tetris" project in the Projects bar on the left. Go to Build Options -> Linker Settings -> Other Linker Settings, type the following text without inverted commas
   "-lmingw32 -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf"
5. Copy every .dll file from the "dependencies" folder into the main project folder
6. Build and run