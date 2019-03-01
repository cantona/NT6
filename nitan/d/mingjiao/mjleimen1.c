// Room: /d/mingjiao/mjleimen1.c
// Jan.5 1997 by Venus

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "門口");
        set("long", @LONG
前面就是明教的『雷字門』了，這裏是明教中西域弟子修煉的地
方。西域風俗大異中土，他們的生活習慣以及使用物品也與中土迥異。
LONG );
    set("exits", ([
        "enter" : __DIR__"sushe",
        "northeast" : __DIR__"mjleimen",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}