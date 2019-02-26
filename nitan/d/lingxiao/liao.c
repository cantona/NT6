inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "居室");
        set("long", @LONG 
這是廖自勵的房間。四位長老中，以他最為生性多智，有人
説若不是當年先師仙去之時，他不在凌霄城內，而等廖自勵回來
之時，大局已定，那這掌門之位必為他囊中之物。這房間內擺滿
了書，從《孫子兵法》到《史記》，盡皆是權謀爭鬥之書。
LONG);
        set("exits",([
                    "south"  : __DIR__"zoulang3", 
        ]));
        set("objects", ([  
                __DIR__"npc/liao" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
