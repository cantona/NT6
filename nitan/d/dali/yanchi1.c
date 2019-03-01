//Room: /d/dali/yanchi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池堤岸");
        set("long", @LONG
這裡沿湖堤岸遍植白色的素馨花，故又稱『銀棱河』；而它的一
條分支，堤岸栽種黃色的迎春花，故稱『金棱河』，或金汁河。兩河
同為滇池的出水口，又稱海口。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"    : "/d/dali/dianchi",
            "west"     : "/d/dali/jinzhihe",
            "eastup"   : "/d/dali/yanchi2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}