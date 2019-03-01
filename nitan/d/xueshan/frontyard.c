// Code of ShenZhou
// Summer 9/12/96
#include "room.h"

inherit ROOM;

void create()
{
        set("short", "前院");
        set("long", @LONG
前院面闊七間，正中供逢著鬆讚幹不像。這裡是觀看大活佛主持
法會和觀看法舞之地。前院四周立有大型明柱一百四十根，上面盡是
彩繪佛傳故事圖。
LONG );
        set("exits", ([
              "south" : "/d/xueshan/shanmen",
                "north" :"/d/xueshan/guangchang",
        ]));

        set("objects", ([
                 "/d/xueshan/npc/fsgelun" : 1,
//                "/d/xueshan/obj/jitan" : 1,
        ]));

        set("cost", 1);
        setup();
        set("outdoors","qilian-shan");
}
/*
int valid_leave(object me, string dir)
{
        object ob;
        ob=(present("fa tan", (environment(me))));
        if( objectp(ob) && query("name", me) == query("pending", ob )
         && query("burning", ob) )
                return notify_fail("你法事沒做完就想走？\n");
        return ::valid_leave(me, dir);
}
*/
