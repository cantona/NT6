//Room: /d/dali/shufang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short", "書房");
        set("long", @LONG
這是大理國鎮南王的書房，靠窗放著一個大木桌桌上放著不少書，
靠牆的地方還有一個書架，鎮南王經常在這裡看書。
LONG );
        set("objects",([
            CLASS_D("dali")+"/zhudanchen":1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/tingfang",
        ]));
	set("coor/x", -19091);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}