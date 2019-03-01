// Room: /d/huangshan/lianrui.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "蓮蕊峰");
        set("long", @LONG
蓮蕊峰與蓮花峰相互依托，這裡恰似蓮花之蕊，峰不高，可怪石參
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