//Room: road1.c
//Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","青石大道");
        set("long", @LONG
這是一條通往成都的大青石道，兩旁綠樹蔭蔽，空氣十分清新。
成都平原向稱天府之國，這裡四周田野稻浪滾滾，平平展展的大地上，
偶爾會出現一大叢翠竹濃蔭，細細認去，都是人家居處。
LONG );
        set("outdoors", "emei");
        set("exits",([ /* sizeof() == 1 */
            "east"       : "/d/emei/qsjie1",
            "southwest"  : __DIR__"road2",
            "northwest"  : __DIR__"liangting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15160);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}