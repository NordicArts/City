#include "./Main.hpp"
#include <Game.hpp>
#include <GameState/Start.hpp>

namespace NordicArts {
    int main() {
        Game oGame;
        oGame.pushState(new GameStateStart(&oGame));
        oGame.gameLoop();

        return EXIT_SUCCESS;
    }
}

int main() {
    NordicArts::main();
}
