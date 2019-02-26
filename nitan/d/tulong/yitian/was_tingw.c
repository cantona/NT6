#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "側廳");
        set("long", @LONG
這裏是萬安寺的側廳，地上擺着幾個蒲團。
LONG );
        set("exits", ([
                "east" : "/d/tulong/yitian/was_zoulang1",
        ]));

        set("outdoors", "beijing");
        setup();
}

