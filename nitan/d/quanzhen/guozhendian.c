// guozhendian.c 過真殿
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "過真殿");
        set("long", @LONG
這裡是大堂旁邊的一個側殿，也是接待重要客人的地方。殿不
大，只擺放著一張桌子和幾把椅子。桌上擺放著一盆青山隱隱的盆
景，牆壁上掛著一些字畫。從這裡往北，好象有一座四層的小塔。
LONG
        );
        set("exits", ([
                "west"  : __DIR__"cetang",
                "south" : __DIR__"datang3",
                "north" : __DIR__"cundaota1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2780);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}