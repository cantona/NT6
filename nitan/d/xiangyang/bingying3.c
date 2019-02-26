// Room: /d/xiangyang/bingying3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "兵營");
        set("long", @LONG
這裏是兵營，密密麻麻到處都是官兵，有的在武將的指揮下列隊
操練，有的獨自在練功，有的坐着、躺着正在休息。南牆下坐着主帥，
不動聲色地巡視着四周。看到你進來，他們全都瞪大眼睛盯着你。
LONG );
        set("item_desc", ([
                "dong" : "\n",
        ]));

        set("exits", ([
                "east" : __DIR__"southjie3",
        ]));
        set("objects", ([
                __DIR__"npc/pian" : 1,
                __DIR__"npc/zuo"  : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7830);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}