// Room: /d/suzhou/yingxiaoting.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "迎笑亭");
        set("long",@long
這裏是靈巖山半山上的一座小亭子，從山下上山的遊客到了這裏都
歇歇腳。俯望山下景色，遠處一片碧波，在水天之間，點點銀光，煞是
宜人。
long);
        set("outdoors","suzhou");
        set("objects",([
                __DIR__"npc/seng" : 1,
        ]));
        set("exits",([
                "westdown" : __DIR__"lingyanshan",
                "southup" : __DIR__"shiyuan",
        ]));
	set("coor/x", 1120);
	set("coor/y", -1140);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}