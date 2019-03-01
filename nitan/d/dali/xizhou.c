//Room: /d/dali/xizhou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","喜州城");
        set("long",@LONG
喜州又名大鱉城，是大理南部大城，自唐代已極繁榮，邑居人戶
尤眾，商貿甚繁榮，有大量他國客商來此交易，採購大理產的金銀、
絲織品、象牙、皮毛等，其中又以來自印度的客商最多，前來販絲綢
往波斯甚至更遠的西方。
LONG);
        set("objects", ([
           __DIR__"npc/keshang": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"tianweijing",
            "east"       : __DIR__"kedian",
            "southwest"  : __DIR__"zhulin",
            "south"      : __DIR__"feilihu",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}