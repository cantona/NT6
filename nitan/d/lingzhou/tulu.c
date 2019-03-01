// Room: /lingzhou/tulu.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "林中土路");
        set("long", @LONG
這是山間的土路，勉強可以通行一輛大車，路面上有兩條深深的車
轍印，路邊山坡上全是參天巨木，看上去密不透風，這裡很幽靜，除了
偶爾幾聲鳥叫才能打破寂靜。土路向東北蜿蜒延伸轉了個彎，西南面隱
約可以看見林中一面大屋頂上的旗幟。
LONG );
        set("exits", ([
                "south"     : __DIR__"luorilin2",
                "northeast" : __DIR__"kongdi", 
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2955);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}