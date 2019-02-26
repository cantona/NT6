//Room: /d/dali/bingying.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","兵營");
        set("long", @LONG
大理國雖小，卻重視精兵良將。然屈人必先屈志，兵戈乃下下之
策，段氏大理先與北鄰宋朝修和，再以姻親拉攏當地人，多年無戰事。
這是城裏的鐵騎營，為皇族的嫡系，裝備給養無不優於中原地方。軍
士們嚴縝以待，盔甲鮮明，刀劍鋒利。
LONG );
        set("objects", ([
           "/d/dali/npc/bing": 2,
           "/d/dali/npc/weishi1": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/dahejiewest",
            "west"   : "/d/dali/majiu",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}