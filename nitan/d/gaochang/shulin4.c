// Room: /d/gaochang/shulin4.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
        set("short", "高昌迷宮");
        set("long", @LONG
這是條黑沈沈的長甬道，甬道前出現了三條岔道。迷宮之內並無足
跡指引，你不知道要往哪條路走。俯身細看，見左首，右首和前方三條
路上都有淡淡的足跡。你似乎迷失了方向，象沒頭蒼蠅般到處亂闖。
LONG
        );
        set("outdoors", "gaochang");
        set("no_drop",1);
        set("exits", ([
                "east" : __DIR__"shulin5",
                "west" : __DIR__"shulin"+(random(10)+2),
                "south" : __DIR__"shulin"+(random(10)+2),
                "north" : __DIR__"shulin3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -38000);
        set("coor/y", 11000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}