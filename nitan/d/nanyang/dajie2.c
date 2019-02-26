// Room: /d/nanyang/dajie2.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
南陽城自古便是關、洛通荊、襄的必經之路。城雖不大，卻很是整
潔，且民風淳樸。街西有一家小小的店鋪，賣些酒水，肉食給過往的行
人。東北面是一個大廟。
LONG);
        set("exits",([
                "north"     : __DIR__"beimen",
                "south"     : __DIR__"nanyang",
//                "west"      : __DIR__"xiaodian",
                "northeast" : __DIR__"wuhouci",
        ]));
        set("objects",([
                __DIR__"npc/man":1,
        ]));
        set("outdoors","nanyang");
	set("coor/x", -6940);
	set("coor/y", 780);
	set("coor/z", 0);
	setup();
        set("no_clean_up", 0);
}