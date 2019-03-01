//Room: /d/dali/cangshanzhong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","蒼山中部");
        set("long",@LONG
你行走在蒼山中部山顛，此間地形極險，兩邊山高入雲，中間一
條崎嶇不平的山路。路西不遠一條大河自北略偏西方向南流過，隆隆
水聲遙遙可聞，正是南詘名川--瀘水。此路是自西川和土番入大理的
必經之途，時有客商過往。由此向南穿越蒼山可抵下關城，北面不遠
則是出蒼山的山口。
LONG);
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"jianchuan",
            "southwest"  : __DIR__"cangshanlu1",
            "southeast"  : __DIR__"xiaguan",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19180);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}