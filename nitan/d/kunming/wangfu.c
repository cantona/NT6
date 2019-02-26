#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "王俯大門" );
        set("long", @LONG
這裏便是雲南平西王俯的大門，兩邊個有一個威武的大石
獅子，高大的朱漆大門緊緊的閉着，幾個親兵嚴密的注視着來
往的人，沒什麼事，最好別在這裏溜達。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south"    :__DIR__"beidajie",
                "north"   :__DIR__"wangfu1",
        ]));

        set("objects",([
                __DIR__"npc/qinbing":4,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7190);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" &&
           objectp(present("qin bing", environment(me))))
                return notify_fail(CYN "親兵攔住你説道：王府大院，閒雜人"
                                   "等一律迴避。\n" NOR);                
        return ::valid_leave(me, dir);
}