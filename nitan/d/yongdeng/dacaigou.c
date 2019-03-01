// Room: /huanghe/dacaigou.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "打柴溝");
        set("long", @LONG
打柴溝地勢不如烏鞘嶺那樣險要，比較平坦，官道兩邊全是密林，
時常有樵夫砍柴的聲音從林中傳出。
LONG );
        set("exits", ([
                "southwest" : __DIR__"gulang",
                "north"     : __DIR__"wuqiao",
        ]));
        set("objects", ([
                __DIR__"npc/qiaofu" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16100);
	set("coor/y", 4220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}