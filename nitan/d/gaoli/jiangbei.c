// /d/gaoli/xuanwumen
// Room in 高麗
#include <ansi.h>
inherit ROOM;



void create()

{
set("short", "鴨綠江北岸");

        set("long", @LONG
這裏是鴨綠江的北岸。從這裏乘船南下，就可以到高麗了。這裏的
人比較多，這裏停泊着幾艘小船，看遠處還有小船要靠近岸來。
LONG
        );
        
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"milin1",
"south" : __DIR__"jiangnan",
                               
        ]));
       setup();
        
}
