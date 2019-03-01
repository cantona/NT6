// liuzhuang.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
int do_knock(string arg);

void create()
{
        set("short", "劉莊");
        set("long", @LONG
莊園的大匾上是“劉莊”兩個大字。大門(gate)緊閉，裡面靜悄
悄的一點聲音都沒有。
LONG);
        set("exits", ([
                    "east"  : __DIR__"dadao3",
                "south" : __DIR__"liuzhuang1",
                "north" : __DIR__"liuzhuang2",
        ]));
        set("item_desc", ([
                   "gate" : "朱紅的大門緊閉著，敲敲(knock)看吧。\n"
        ]));
        set("objects", ([
                __DIR__"npc/guanjia" : 1,
                __DIR__"npc/jiading" : 2,
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 770);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_knock", "knock");
}

int do_knock(string arg)
{
        object me;

        me = this_player();
        message_vision("$N“咚，咚，咚，。。。”地敲著門，可裡面卻一"
                       "點動靜都沒有。\n", me);
        return 1;
}