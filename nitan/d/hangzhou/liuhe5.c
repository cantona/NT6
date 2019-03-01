// liuhe5.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
這裡是六和塔的五層。窗(window)外是濃妝淡抹的西子湖，塔
中玲瓏八角，青磚砌地，雕欄飛檐間粘連了些許蛛網。
LONG);
        set("exits", ([
            "down"  : __DIR__"liuhe4",
            "up"    : __DIR__"liuhe6",
        ]));
        set("objects", ([
            __DIR__"honghua/wei" :1,
        ]));
        set("item_desc", ([
            "window": "從窗口望出去，錢江東去。近處農田中，有一農夫正荷鋤耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 49);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("wei chunhua", environment(me))))
            return notify_fail("衛春華大吼一聲：我有九條命，你有幾條？放馬過來！\n");
        return ::valid_leave(me, dir);
}