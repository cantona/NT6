// Room: /d/changcheng/changcheng15.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
由于長期受到風沙的侵蝕，一小段城牆已經倒塌。你只好暫時從旁
邊的小路繞過去。從這裡你可以看到，雖然有的地方已經倒塌，但整條
長城依然雄偉的屹立在山頂，並向兩邊山脊延伸出去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "northwest" :__DIR__"changcheng16",
                "east"      :__DIR__"changcheng14",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12000);
        set("coor/y", 9000);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}