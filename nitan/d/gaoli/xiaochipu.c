// /d/gaoli/xiaochipu
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "小吃店");
        set("long", @LONG
這是一家很破很舊的小店。只有三、兩張桌子零亂的擺放着，桌上
還粘着一層厚厚的油垢。牆則早已被油煙薰去了原來的本色。這裏不賣
其它食物，只賣一些小吃，價格低廉。
LONG
        );
set("exits", ([
               "south":__DIR__"baihu-2", 
        ]));
set("objects", ([
                "/d/gaoli/npc/li" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
