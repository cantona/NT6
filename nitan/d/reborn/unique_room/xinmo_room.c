// xinmo_room.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "心魔深處" NOR);
        set("long", @LONG
幻境裏到處是迷霧瀰漫，周邊的景物似有似無，虛無縹緲。
LONG );

        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "maze");
        set("objects", ([
                "/d/reborn/npc/shadow": 5,   
                "/d/reborn/npc/xinmo": 1,   
        ]));
	setup();
}
