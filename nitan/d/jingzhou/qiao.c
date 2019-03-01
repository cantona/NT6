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
        set("outdoors", "jingzhou");

        set("exits", ([
                "south" : __DIR__"qiao2", 
                "north"  :__DIR__"jiangbei",
        ]));
        set("coor/x", -7100);
	set("coor/y", -2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}