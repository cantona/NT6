// Room: /d/huanghe/road6.c
// Last Modified by winder on Apr. 10 2000
inherit ROOM;
void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條黃土路上。陝西的地面，就是看不盡的黃土。向南方望
去，遠遠有高山插雲，近處好象有個小小村落。隱隱傳來犬吠雞啼，給
你長途的奔波帶來一絲生氣。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "southeast" : "/d/village/wexit",
                "north"     : __DIR__"road5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1010);
        set("coor/y", 300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
