//Room: /d/dali/zonglichu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","國務總理處");
        set("long", @LONG
總理處是鎮南王皇太弟總理國務之處，滿桌的奏章整理得井井有
條。四周擺了很多茶花，爭奇鬥艷。茶花是大理國花，看來主人對它
也是鐘愛有加。
LONG );
        set("objects", ([
            "/d/dali/obj/shanchahua": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/sikong",
            "south"  : "/d/dali/wfdating",
            "east"   : "/d/dali/sima",
            "west"   : "/d/dali/situ",
        ]));
	set("coor/x", -19121);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}