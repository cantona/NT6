// Room: /d/quanzhou/guitangxiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "桂壇巷");
        set("long", @LONG
桂壇巷順着施府高牆蜿蜒而出，一面是潺潺流水的溝渠，幽暗寧靜。
桂壇巷西南面便是承天寺。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"xuetang",
                "north"     : __DIR__"jiangjunfu",
                "southwest" : __DIR__"chengtiansi",
        ]));
	set("coor/x", -880);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}