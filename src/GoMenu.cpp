#include "../include/GoMenu.hpp"

#include "../include/graphics.h"
// C
#include <stdint.h>

Hcl::Vector<GoMenuEntry> GoMenu::_c;

void GoMenu::main()
{
    log("[GoMenu]: started");
    window goMenu(148,200,0,768-208,/*locale->tr(*/"Go! Menu"/*)*/  /*tNames[LANG_RUS][LC_NAME_GOMENU]*/,"");
    drawObj(goMenu,false);

    GoMenuEntry* en = 0;
    int i, s = 0;
    char c;
    bool run = true;
    while(run)
    {
        for(i = 0; i < _c.size(); ++i)
        {
            if(i == s)
                vgaWriteStr(goMenu.x+5, goMenu.y + 21 + i * 8, _c[i].name, MAGENTA, LIGHT_GREY);
            else
                vgaWriteStr(goMenu.x+5, goMenu.y + 21 + i * 8, _c[i].name, WHITE, LIGHT_BLUE);
        }
        c = inb(0x64);
        switch(c)
        {
            case 0x48:
                if(s)
                    --s;
                break;
            case 0x50:
                if(s < _c.size() - 1)
                    ++s;
                break;
            case 0x28:
                en = &_c[s];
            case 0x1:
                run = false;
                break;
        }
    }
    delWin(goMenu);
	drawWallpaper();
	drawDesktop();
    if(en)
        en->callback();
}

void GoMenu::addEntry(GomenuEntry& en)
{
/*    if(en.uid >= _c.size())
        _c.resize(en.uid);
    if(_c[en.uid])
        log("[GoMenu]: warning: attempt to register existing item, aborting");
    else
        _c[en.uid] = en;*/
    _c.pushBack(en);
}