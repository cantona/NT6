#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "小路");
        set("long", @LONG
這裡是一條崎嶇的黃土小路，路旁雜草叢生，西邊只見黃土飛揚，
好象是條大官道。東面則有一座青山，山上樹木茂密。
LONG );
        set("exits", ([
                  "east" : __DIR__"road5",
                  "west" : __DIR__"road7",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -380);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
