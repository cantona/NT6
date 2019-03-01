// jujingyuan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "聚景園");
        set("long", @LONG
漫步園中，只見湖傍遍置垂柳。柳樹叢中，種了不少碧桃。東風
送暖之時，這裏“楊柳千條拂面絲，綠煙金穗不勝吹”。詩人劉禹錫
的“桃紅李白皆誇好，須得垂楊相發揮”形容的恰到好處。東面是清
波門，往東北便是柳浪橋。
LONG);
        set("exits", ([
            "east"      : __DIR__"qingbomen",
            "northeast" : __DIR__"liulangqiao",
        ]));
        set("objects", ([
            __DIR__"npc/jian-ke" : 1,
            __DIR__"npc/honghua2" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "xihu");
//        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}