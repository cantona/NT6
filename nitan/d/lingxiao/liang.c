inherit ROOM;

#include <ansi.h> 

void create()
{
        set("short","居室");
        set("long",@LONG
這是樑自進的房間，他生性單純，與廖自勵正好相反。他從
小就在凌霄城中練功習武，連大雪山也未下過一步，所以他的武
功在五代弟子中，是僅次于白自在的。他的房間樸素自然，僅有
一床一桌。除此之外，別無他物。 
LONG);
        set("exits", ([
                    "north"  : __DIR__"zoulang3", 
        ]));
        set("objects", ([  
                __DIR__"npc/liang" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
