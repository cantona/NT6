// Room: /d/taiwan/luermen.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "鹿耳門");
        set("long", @LONG
清政府治台之初，以台灣孤懸海外，易為姦民捕逃之藪，而禁止移
民，後因私渡日多，乃予開放，但僅限福建廈門與台南鹿耳門兩岸獨口
對渡，因此府治成為全台唯一的吐納港。此情況直至鹿港、八裡坌開港
後始有改變。
LONG );
        set("exits", ([
                "east" : __DIR__"anping",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taiwan");
        set("coor/x", 2490);
        set("coor/y", -7030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
