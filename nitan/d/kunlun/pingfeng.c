// Room: /d/kunlun/pingfeng.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石屏風");
        set("long",@long
這是一個巨大的屏風，用崑崙山特產的汗白玉雕成，屏風上的圖案
是崑崙派的師祖崑崙三聖何足道挑戰少林的風姿，英姿挺拔，頗有一派
宗師之象。屏風後面就是崑崙派的前廳了。
long);
        set("exits",([
                "south" : __DIR__"guangchang",
                "north" : __DIR__"qianting",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40050);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
