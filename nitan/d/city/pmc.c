#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIG+BLINK"拍賣場"NOR);
        set("long", @LONG
這裏是專門為玩家們拍賣(paimai)物品而設的地方。
LONG );
        set("no_fight",1);
    set("exits", ([
        "north"  : "/d/city/pm_road1",
        "out"  : "/d/city/kedian",
    ]));
    set("objects", ([
        "/d/city/npc/paimaishi" : 1,
    ]));
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
