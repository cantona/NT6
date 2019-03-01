// Room: /d/quanzhou/yanyu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "萬國煙雨樓");
        set("long", @LONG
「人道不思歸，煙雨伴君眠」，傍湖而建，情趣盎然的萬國煙雨樓
名雖酒樓，實是遠近聞名的一景。樓分兩層，一進大門，即可見園林中
亭台樓榭，假山流水，一池碧水，荷藕映紅。環池漫步，客房綿延。
LONG );
        set("exits", ([
                "west"   : __DIR__"road2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}