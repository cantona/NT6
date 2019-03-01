//Room: /d/dali/luyuxi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","綠玉溪沿岸");
        set("long",@LONG
一條頗寬敞的土路沿著綠玉溪南岸橫貫東西，一邊是涓涓溪流碧
波盪漾，另一邊是青山翠柳，鬱鬱蔥蔥的林木。東面有橋渡溪通向大
理城南門，西去不遠就是五華樓了。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "east"      : __DIR__"shuangheqiao",
            "west"      : __DIR__"gudao",
            "south"     : "/d/wudu/road1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}