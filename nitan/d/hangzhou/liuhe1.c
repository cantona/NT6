// liuhe1.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
這裡是六和塔的底層。窗(window)外是濃妝淡抹的西子湖，塔
中玲瓏八角，青磚砌地，雕欄飛檐間粘連了些許蛛網。
LONG);
        set("exits", ([
            "out"   : __DIR__"liuheta",
            "up"    : __DIR__"liuhe2",
        ]));
        set("objects", ([
            __DIR__"honghua/an" :1,
            __DIR__"honghua/meng" :1,
        ]));
        set("item_desc", ([
            "window": "從窗口望出去，錢江東去。近處農田中，有一農夫正荷鋤耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 9);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("an jiangang", environment(me))))
            return notify_fail("安健剛一把攔住你：瞎竄什麼，過來吧你給我！\n");
        if (dir == "up" &&
            objectp(present("meng jianxiong", environment(me))))
            return notify_fail("孟健雄一把攔住你：要上樓，先過了我這關！\n");
        return ::valid_leave(me, dir);
}