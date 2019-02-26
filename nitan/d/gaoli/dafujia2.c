// /d/gaoli/dafujia2
// Room in 高麗
// rich 99/03/28
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIC"大富之家"NOR);
        set("long", @LONG
你信步走進這家的大廳。整個大廳佈置的極其豪華奢侈，一看就知
道不是普通百姓所住的地方。廳中擺着一張杉木圓桌和幾張椅子，桌上
是一套精緻的宜興瓷器。
LONG
);
        set("exits", ([ 
        "south" : __DIR__"dafujia1",
        ]));
set("objects", ([
                "/d/gaoli/npc/jin" : 1,
                __DIR__"npc/yahuan":1,
        ]));
      setup();
        replace_program(ROOM);

}
