#include <engine.h>

int main()
{
    if (!Engine::init() || !Engine::start()) return 1;
    Engine::close();
    return 0;
}