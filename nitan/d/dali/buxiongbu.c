//Room: /d/dali/buxiongbu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","步雄部");
        set("long",@LONG
這裡屬江川路，是擺夷的一支--些麼徒蠻聚居的地方。此地較偏
遠，鎮子也不大，南面一片汪洋叫做星雲湖，四面山清水秀，桑林密
布。鎮北是一片小平原，有些農田。此間桑樹多，產絲，鄉間民婦多
擅紡絲織麻。
LONG);
        set("objects", ([
           __DIR__"npc/bshangfan": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "west"   : __DIR__"banshan",
            "east"   : __DIR__"yangcanfang",
            "south"  : __DIR__"xingyunhu",
            "north"  : __DIR__"nongtian5",
        ]));
	set("coor/x", -19020);
	set("coor/y", -6910);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}