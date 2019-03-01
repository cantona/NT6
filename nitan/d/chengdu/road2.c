// Room: road2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","青石大道");
        set("long", @LONG
這是一條通往成都的大青石道，兩旁綠樹蔭蔽，空氣十分清新。
成都平原向稱天府之國，四野雞鳴犬吠，交替起落，一派安樂氣息。
西面隱隱可以看到成都城門了。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"road1",
            "west"       : __DIR__"fuheqiaoe",
            "east"      : __DIR__"shudao19",            
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15170);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}