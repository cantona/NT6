// Room: /d/wuxi/road16.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "山道");
        set("long", @LONG
大驛道至此開始上山，四周看去羣山環繞，但是卻都是一些低矮
起伏的丘陵。山上覆蓋着的都是青綠如一的叢林，縱眼望去，了無人
煙，遠遠依稀聞聽鳥鳴獸嘯。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"  : __DIR__"road17",
                "east"     : __DIR__"road14",
        ]));
        set("coor/x", 980);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}