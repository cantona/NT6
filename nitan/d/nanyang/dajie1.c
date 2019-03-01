// Room: /d/nanyang/dajie1.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
南陽城自古便是關、洛通荊、襄的必經之路。城雖不大，卻很是整
潔，且民風淳樸。大街上人喊馬嘶，盡是南來北往的行商。街西邊是一
家商號。
LONG);
        set("exits",([
                "north" : __DIR__"nanyang",
                "south" : __DIR__"nanmen",
                "west"  : __DIR__"shop",
        ]));
        set("objects",([
                "/d/taishan/npc/tiao-fu" : 1,
        ]));
        set("outdoors","nanyang");
	set("coor/x", -6940);
	set("coor/y", 760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}