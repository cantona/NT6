//Room: /d/dali/yujia.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","漁家");
        set("long",@LONG
休獵部專事漁獵，很少蓄養牲畜或耕作。這是一座普通的竹樓，
下層通常的牲畜圈是修補竹筏漁網的工棚，一位台夷婦女正在細心地
"編織漁網。樓邊有一排木架，掛滿開過膛的魚，正在涼曬魚乾。
LONG);
        set("objects", ([
                 __DIR__"npc/funu": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "east"  : __DIR__"hexi",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6980);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/yj", 1, me);
        }
}