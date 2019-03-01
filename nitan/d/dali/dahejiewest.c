//Room: /d/dali/dahejiewest.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大和街");
        set("long", @LONG
這是一條青石板路，兩邊種了不少柏樹，顯得莊嚴肅穆。南面是
大理城的守軍駐地，隱隱可以聽到兵士們操練的號子聲，向北是土司
府，是當今皇太妃刀氏一族的世襲衙門。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "east"   : "/d/dali/shizilukou",
            "north"  : "/d/dali/tusifu",
            "south"  : "/d/dali/bingying",
            "west"   : "/d/dali/zsh_dldamen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}