#include "../include/GoMenu.hpp"

#include "../include/HCL/Std.hpp"
#include "../include/FbGraphics.hpp"
#include "../include/Syslog.hpp"
#include "../include/Window.hpp"
// C
#include <stdint.h>

// I have no idea where they are, but i'm sure they mut be removed
void drawWallpaper();
void drawDesktop();

Hcl::Vector<GoMenuEntry> GoMenu::_c;

char* itoa(int);

void GoMenu::main()
{
    log("[GoMenu]: started");
    Window goMenu("Go! Menu", 0, 560, 148, 200);
    drawObj(&goMenu,false);

    GoMenuEntry* en = 0;
    int i, s = 0;
    char c;
    bool run = true;
    
    while(run)
    {
        for(i = 0; i < _c.getSize(); ++i)
        {
            if(i == s)
                vgaWriteStr(goMenu.x+5, goMenu.y + 21 + i * 8, _c[i].name, MAGENTA, BROWN);
            else
                vgaWriteStr(goMenu.x+5, goMenu.y + 21 + i * 8, _c[i].name, WHITE, LIGHT_BLUE);
        }

        c = inb(0x60);
        switch(c)
        {
            case 0x48: // UP
                if(s)
                    --s;
                break;
            case 0x50: // DOWN
                if(s < _c.getSize() - 1)
                    ++s;
                break;
            case 0x28: // ENTER
                en = &_c[s];
            case 0x1: // ESCAPE
                run = false;
                break;
        }
    }
    delWin(&goMenu);
    drawWallpaper();
    drawDesktop();
    if(en)
        en->callback();
}

void GoMenu::addEntry(GoMenuEntry& en)
{
/*    if(en.uid >= _c.size())
        _c.resize(en.uid);
    if(_c[en.uid])
        log("[GoMenu]: warning: attempt to register existing item, aborting");
    else
        _c[en.uid] = en;*/
    uint64_t i;
    for(i = 0; i < _c.data + 1; ++i)
    {
        vgaWriteStr(500 + i * 8, 400, "_", MAGENTA, BROWN);
    }

    _c.pushBack(en);
    
    for(i = 0; i < _c.data->_begin + 1; ++i)
    {
        vgaWriteStr(500 + i * 8, 500, "!", MAGENTA, BROWN);
    }
    for(i = 0; i < _c.data->_end + 1; ++i)
    {
        vgaWriteStr(500 + i * 8, 550, "!", MAGENTA, BROWN);
    }
    for(i = 0; i < _c.data->_endall + 1; ++i)
    {
        vgaWriteStr(500 + i * 8, 600, "!", MAGENTA, BROWN);
    }
}