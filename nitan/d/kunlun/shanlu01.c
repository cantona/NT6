// Room: /d/kunlun/shanlu01.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "昆侖山路");
        set("long",@long
這裡已經是昆侖派的地方了，路邊花草滿地，雖然是寒冬，這裡卻
仍然生機勃勃，到處傳來鳥獸的叫聲，前面山上就是昆侖派的居所了，
下面是來的時候的山門。
long);
        set("exits",([
                "westdown" : __DIR__"shanmen",
                "northup"  : __DIR__"shanlu02",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40000);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}