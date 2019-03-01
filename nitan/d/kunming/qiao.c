#include <room.h>
inherit ROOM;

void create()
{
        set("short", "獨木橋");
        set("long", @LONG
這裡是一座獨木橋，也不知是什麼時候架起來的，走在上
面搖搖晃晃的，很是危險。如果你要過河的話，就只有走這裡。
從橋上望下去，只見急流勇潺，一掉下去，肯定沒命。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "south" : __DIR__"qiao2", 
                "north"  :__DIR__"road5",
        ]));
        setup();
        replace_program(ROOM);
}