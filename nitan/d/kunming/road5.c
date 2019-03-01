#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長江北岸");
        set("long", @LONG
你快步來到了長江北岸，只見這裡波濤滾滾，滔滔江水向
東流去。岸邊立有一塊碑(bei)，前面不遠處有座獨木橋。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"qiao", 
                "north" :__DIR__"road4",                
        ]));
        set("item_desc", ([
                "bei" : WHT "\n\n\n            ※※※※※※※※※※※※※※※※\n"
                        "            ※                            ※\n"
                        "            ※" NOR + HIW "     通      天      河" NOR +
                        WHT "     ※\n"
                        "            ※                            ※\n"
                        "            ※※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 2,
        ]));
        setup();
        replace_program(ROOM);
}
