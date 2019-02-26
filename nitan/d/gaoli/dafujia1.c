// /d/gaoli/dafujia1
// Room in 高麗
// rich 99/03/28
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIC"大富之家"NOR);
        set("long", @LONG
這是一家高麗城內的富貴人家，這家主人經商一輩子，攢了不少錢，
在高麗城內蓋了這麼個大宅子，門口立着兩個大石獅子，站着兩個家丁。
LONG
);
        set("exits", ([ 
        "south": __DIR__"baihu-1",
        "north": __DIR__"dafujia2",
        ]));
set("objects",([
                "/d/gaoli/npc/jiading" : 2,
        ]));
      setup();
        replace_program(ROOM);

}
