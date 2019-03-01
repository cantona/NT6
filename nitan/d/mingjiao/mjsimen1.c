// Room: /d/mingjiao/mjsimen1.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "廣場");
        set("long", @LONG
這裡是一片庭院中央的廣場，整個廣場由大塊的青石舖成，極為
平坦。但因年代久遠，都有些破損。叢叢小草從石板的縫隙中長了出
來。廣場四面有幾條小道，通向明教的『天地風雷』四門。
LONG );
    set("exits", ([
        "north"     : __DIR__"mjsimen",
        "northwest" : __DIR__"mjtianmen",
        "northeast" : __DIR__"mjdimen",
        "southeast" : __DIR__"mjfengmen",
        "southwest" : __DIR__"mjleimen",
    ]));
    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
