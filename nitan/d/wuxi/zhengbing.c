// Room: /d/wuxi/zhengbing.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "徵兵場");
        set("long", @LONG
這裏是新兵徵募處，門口有塊木牌 (mupai)，裏面擠滿了人，有乳
臭未乾的少年，更多的是身強力壯的青年人，每個的人臉上都是對未來
的憧憬。如果你想報效國家，征戰沙場，或是出人頭地，這是能實
現你夢想的地方。
LONG );
        set("outdoors", "wuxi");
        set("item_desc", ([
                "mupai" : HIR"
                
         精 忠 報 國

\n"NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"eastroad1",
        ]));
        set("objects", ([
                __DIR__"npc/guan" : 1,
        ]));
        set("coor/x", 1050);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}