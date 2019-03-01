//Room: /d/dali/shizilukou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","十字路口");
        set("long", @LONG
這是大理城內的主要商貿場所。形形色色的叫賣聲在耳邊此起彼
伏，連綿不絕。路上車水馬龍，各色行人摩肩接踵，熱鬧非凡。大道
兩旁高立了兩座樓牌，西首是御林軍的駐地，東面則是民居。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/center",
            "south"  : "/d/dali/southgate",
            "east"   : "/d/dali/dahejieeast",
            "west"   : "/d/dali/dahejiewest",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}