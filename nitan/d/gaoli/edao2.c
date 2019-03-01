// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的行商，
趕著大車的馬夫，熙熙攘攘，非常熱鬧。不時還有兩三騎快馬從身邊飛
馳而過，揚起一路塵埃。道路兩旁是整整齊齊的楊樹林。
LONG
        );

        set("exits", ([
                "east" : __DIR__"edao1",
                "southwest":__DIR__"shanlu3",
        ]));

         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


