// Room: /d/kunlun/shanlu04.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石階路");
        set("long",@long
走過盤山路，就是一段很平整的石階山路。前面傳來刀劍相碰的聲
音，快到了，你不由得加快了腳步，遠遠望去，似乎是個大廣場，圍著
不少人在練武。
long);
        set("exits",([
                "southdown" : __DIR__"shanlu03",
                "north"     : __DIR__"guangchang",
                "northwest" : __DIR__"guangchangw",
                "northeast" : __DIR__"guangchange",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40030);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}