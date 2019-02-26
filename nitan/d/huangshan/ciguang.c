// Room: /d/huangshan/ciguang.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "慈光閣");
        set("long", @LONG
已是桃花峯頂，看下面的温泉猶如顆顆明珠，嵌映羣峯，前面就是
青鸞橋，遊人到此一般都要稍做歇息，於是便有了這座慈光閣。
LONG
        );
        set("exits", ([ 
                "southdown" : __DIR__"wenquan",
                "northdown" : __DIR__"qingluan",
                "west"      : __DIR__"taoyuan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}