//Room: /d/dali/piandian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","偏殿");
        set("long", @LONG
這裏是大理國皇宮的偏殿，大理皇帝常在這裏接見心腹大臣，但
現在顯得空空蕩蕩的，往西是長廊。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/hualang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}