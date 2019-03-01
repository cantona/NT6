#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
你走在長江邊上的一條小路上，耳聽著江水嘩嘩的流，心情也覺
得好些，放眼向西看去，只見群山連綿，也不知道何處才是歸途。
LONG );
        set("exits", ([
                  "northeast" :  __DIR__"shudao2",
                  "west" : __DIR__"shudao4",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
                "/d/beijing/npc/girl4" : 1,
        ]));
        set("coor/x", -170);
        set("coor/y", -180);
        set("coor/z", -60);
        setup();
        replace_program(ROOM);
}