// liuhe2.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
這裏是六和塔的二層。窗(window)外是濃粧淡抹的西子湖，塔
中玲瓏八角，青磚砌地，雕欄飛檐間粘連了些許蛛網。
LONG);
        set("exits", ([
            "down"  : __DIR__"liuhe1",
            "up"    : __DIR__"liuhe3",
        ]));
        set("objects", ([
            __DIR__"honghua/xinyan" :1,
            __DIR__"honghua/zhouyi" :1,
        ]));
        set("item_desc", ([
            "window": "從窗口望出去，錢江東去。近處農田中，有一農夫正荷鋤耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 19);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("xin yan", environment(me)))) 
            return notify_fail("心硯哈哈一笑：這裏還沒打過呢，就想上樓。\n");
        if (dir == "up" &&
            objectp(present("zhou yi", environment(me))))
            return notify_fail("周綺俏眼一瞪：沒看見本姑娘在這裏嗎？\n");

        return ::valid_leave(me, dir);
}