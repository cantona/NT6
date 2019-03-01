//Room: /d/dali/jingzhuang4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第四層");
        set("long", @LONG
雕有八坐佛，四隅略大，其中東、南兩佛面目駁落，容不可辨。
坐佛蓮花座皆有梵文佛經。經文尾處刻有『慈濟和尚--大理人』字樣。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang5",
            "down"  : "/d/dali/jingzhuang3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 39);
	setup();
        replace_program(ROOM);
}