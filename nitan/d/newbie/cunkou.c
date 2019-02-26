#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "村口");
        set("long", @LONG
這裏是一片開闊地，遠遠可以望見東方升起的陣陣炊煙，聽到雞
鳴犬吠之聲。如果你想要出村的話，可以問問新手村的守衞（輸入指
令 ask hua about 出村）。
LONG);
        set("exits", ([
                "east" : __DIR__"road1",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/huabo" : 1,
        ]));

        setup();

        replace_program(ROOM);
}
