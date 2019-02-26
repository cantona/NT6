// /d/gaoli/xuanwumen
// Room in 高麗
#include <ansi.h>
inherit ROOM;


void create()

{
set("short", "鴨綠江南岸");

        set("long", @LONG
這裏是鴨綠江的南岸。從這裏乘船北上，就可以到中原的北方了。
這裏停泊着幾艘小船，看遠處還有小船要靠近岸來。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "south" : "/d/changbaishan/shanlu5",
"north" : __DIR__"jiangbei",

                               
        ]));
       setup();
        
}
