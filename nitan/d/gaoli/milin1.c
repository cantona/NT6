// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()

{
set("short", "密林");

        set("long", @LONG
你正走在一茂密的叢林之中。四周都是參天的古樹，遮住了頭上的
陽光。不時有幾只野兔從你的身旁跑過。密林之中，隱藏了很多猛獸毒
蛇，你不禁小心起來。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu2",
                "south" : __DIR__"jiangbei",
               
        ]));
       setup();
        replace_program(ROOM);
}
