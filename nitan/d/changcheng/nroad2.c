// Room: /d/changcheng/nroad2.c
// Last Modified by Winder on Aug. 25 2000

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周的人不是很多。偶爾有幾個
挑夫，匆匆向南走去。不時還有兩三騎快馬從身邊飛馳而過，揚起一路
塵埃。道路兩旁是整整齊齊的楊樹林。從這裏遠遠的就可以望見南邊的
北京城。
LONG );
        set("outdoors", "changcheng");
        set("exits", ([
                "south" : __DIR__"nroad1",
                "north" : __DIR__"juyongguan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -190);
        set("coor/y", 4600);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
