// /d/yixing/clxiaowu.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這是幫眾們酗酒賭錢的的小屋，正中的方桌上杯盤狼籍，有人醉倒
在一旁，不醒人事。隔扇後面另有一張賭桌，幾個幫眾正在吆五喝六地
賭錢。屋內燭光搖曳，似乎沒有人注意你進來。
LONG );
        set("exits", ([
                "east" : __DIR__"clzoulang2",
        ]));
        set("objects",([
                __DIR__"npc/cl_bangzhong3" : 1,
        ]));
        set("resource/water", 1);
        set("coor/x", 269);
	set("coor/y", -991);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}