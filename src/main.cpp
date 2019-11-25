#include "game.h"

int main(void)
{   
    // Configure the logger
    auto logger = spdlog::basic_logger_mt("log-invaders", "invaders.log");
    spdlog::set_default_logger(logger); 
    
    Game game;
    game.run();
    return (0);
}