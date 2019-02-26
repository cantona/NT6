// Room: /d/taishan/tianjie.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "天街");
        set("long", @LONG
此地在南天門東北，這裏有數十户小販聚而成市。道路平整，殿宇
毗連，似天上街市。天街坊東路北，為乾隆行宮及唐代文學家蘇源明讀
書處遺址。從這裏往東南走便是蓮花峯，東北是圍屏山，西南便回到南
天門。
LONG );
        set("exits", ([
                "south"    : __DIR__"xiangshan",
                "eastup"   : __DIR__"weiping",
                "eastdown" : __DIR__"lianhua",
                "westdown" : __DIR__"nantian",
                "northup"  : __DIR__"kongziya",
        ]));
        set("objects",([
                __DIR__"npc/xiao-fan" : 2,
                __DIR__"npc/tiao-fu" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 300);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}