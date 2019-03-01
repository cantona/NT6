//Room: /d/dali/nongtian2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","農田");
        set("long",@LONG
這是一小塊普通的水田地，南詔温暖潮濕，自古以來就以種植水
稻為主。這附近是大理地區少見的平原地形，主要以耕作為生的擺夷
人開墾了一些的農田。田地劃分成小塊，一些擺夷男子正在田裏引着
水牛耕作。有道路穿過農田向東而去。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu2": 1,
           __DIR__"npc/cow": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "west"   : __DIR__"luojiadian",
            "east"   : __DIR__"nongtian3",
            "south"  : __DIR__"langan1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19060);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}