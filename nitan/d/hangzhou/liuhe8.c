// liuhe8.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
這裡是六和塔的八層。窗(window)外是濃妝淡抹的西子湖，塔
中玲瓏八角，青磚砌地，雕欄飛檐間粘連了些許蛛網。
LONG);
        set("exits", ([
            "down"  : __DIR__"liuhe7",
            "up"    : __DIR__"liuhe9",
        ]));
        set("objects", ([
            __DIR__"honghua/chang1" :1,
            __DIR__"honghua/chang2" :1,
        ]));
        set("item_desc", ([
            "window": "從窗口望出去，錢江東去。近處農田中，有一農夫正荷鋤耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 79);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("chang bozhi", environment(me))))
            return notify_fail("常伯志飛身擋住你的去路，臉上一絲表情也沒有！\n");
        if (dir == "up" &&
            objectp(present("chang hezhi", environment(me))))
            return notify_fail("常赫志扭身擋住，臉上沒有一點笑容！\n");
        return ::valid_leave(me, dir);
}