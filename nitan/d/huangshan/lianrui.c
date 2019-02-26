// Room: /d/huangshan/lianrui.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "蓮蕊峯");
        set("long", @LONG
蓮蕊峯與蓮花峯相互依託，這裏恰似蓮花之蕊，峯不高，可怪石參
差不齊，高低起伏，甚是難走，而且並無勝景，所以遊人罕至。
LONG
        );
        set("exits", ([ 
                "northeast" : __DIR__"yuping",
        ]));
        set("objects", ([
                __DIR__"obj/guai" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}