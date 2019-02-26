#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西走廊");
        set("long", @LONG
這裏是一條幹淨的走廊，從兩面看去，可以欣賞到花園裏
的風景，只見各種假山怪石，奇花異草，足見王府之氣派。西
邊是平西王最愛去的書房，門口有幾名親兵在把守。
LONG);
        set("exits", ([
                "west"   :__DIR__"shufan",
                "east"   :__DIR__"xizoulang"
        ]));

        set("objects",([
                __DIR__"npc/qinbing" : 2,
        ]));
	set("coor/x", -16860);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west" &&
           objectp(present("qin bing", environment(me))))
                return notify_fail(CYN "親兵攔住你説道：王爺吩咐了，沒有他"
                                   "的允許，任何人不得進入打擾。\n" NOR);                
        return ::valid_leave(me, dir);
}