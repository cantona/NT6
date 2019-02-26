// Room: /d/quanzhou/yuanhetang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "源和堂");
        set("long", @LONG
這是遠近聞名的蜜餞製作鋪，各色水果經過他們的加工後風味獨特，
甜而不膩，鹹而不過，酸而不澀，又可以長期保存，遠銷海內外。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"zhaiqu3",
                "northeast" : __DIR__"zhaiqu2",
        ]));
	set("coor/x", -920);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}