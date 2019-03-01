// Room: /lingzhou/dalu1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "林中大路");
        set("long", @LONG
這是山間的土路，勉強可以通行一輛大車，路面上有兩條深深的車
轍印，路邊山坡上全是參天巨木，看上去密不透風，這裡很幽靜，除了
偶爾幾聲鳥叫才能打破寂靜。土路向北蜿蜒延伸轉了個彎。
LONG );
        set("exits", ([
                "south"     : __DIR__"luorilin1",
                "north"     : __DIR__"xiaolu1",
                "northeast" : __DIR__"luorilin2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6245);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
