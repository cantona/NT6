#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","小路");
        set("long", @LONG
一條崎嶇的黃土小路，路旁雜草叢生，西邊可以看見荊州的官道，
向東去則可一到達武昌。
LONG );
        set("exits", ([
                  "east" : __DIR__"road6",
                  "west" : __DIR__"guandao1",
          ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -390);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
