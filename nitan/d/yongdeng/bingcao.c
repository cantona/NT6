// Room: /huanghe/bingcao.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "冰草灣");
        set("long", @LONG
冰草灣在營盤水的西南，平時人跡少至，因為當地沙漠里長着一
種神奇的藥草----"冰草"而得名。據説這種藥草能解百毒，所以偶有
人來採這種草，不過沙漠裏常有毒蟲出沒，極為危險。
LONG );
        set("exits", ([
                "southwest" : __DIR__"shixiazi",
                "northeast" : __DIR__"yinpanshui",
        ]));
        set("objects", ([
                __DIR__"npc/wugong" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16090);
	set("coor/y", 4270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}