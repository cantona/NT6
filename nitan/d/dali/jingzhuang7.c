//Room: /d/dali/jingzhuang7.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第七層");
        set("long", @LONG
這裏是經幢的頂部，圓弧形頂篷，向徵天穹。上面刻有諸天神佛，
飛天力士等。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "down"  : "/d/dali/jingzhuang6",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 69);
	setup();
        replace_program(ROOM);
}