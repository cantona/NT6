// liuhed.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
這裡是六和塔的十三層。窗(window)外是濃妝淡抹的西子湖，塔
中玲瓏八角，青磚砌地，雕欄飛檐間粘連了些許蛛網。這裡是塔的最
高處，往外望去，西湖美景盡收眼底。
LONG);
        set("exits", ([
            "down"  : __DIR__"liuhec",
        ]));
        set("objects", ([
            __DIR__"honghua/chen2" :1,
            __DIR__"npc/qianlong" :1,
        ]));
        set("item_desc", ([
            "window": "從窗口望出去，錢江東去。近處農田中，有一農夫正荷鋤耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 129);
	setup();
        replace_program(ROOM);
}