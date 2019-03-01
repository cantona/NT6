//Room: /d/dali/jingzhuang3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第三層");
        set("long", @LONG
雕繞綾坐像四座，坐像間之四面各雕佛及菩薩一組。識者謂北面
多臂觀音，南面為地藏菩薩。合神佛面目和藹，雕刻精細，造形優美。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang4",
            "down"  : "/d/dali/jingzhuang2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}