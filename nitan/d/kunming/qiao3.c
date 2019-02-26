#include <room.h>
inherit ROOM;

void create()
{
        set("short", "獨木橋");
        set("long", @LONG
這裏是一座獨木橋，也不知是什麼時候架起來的，走在上
面搖搖晃晃的，很是危險。如果你要過河的話，就只有走這裏。
從橋上望下去，只見急流勇潺，一掉下去，肯定沒命。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "south" : __DIR__"road6", 
                "north"  :__DIR__"qiao2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}