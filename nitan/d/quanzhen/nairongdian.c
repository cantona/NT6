// nairongdian.c 乃容殿
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "乃容殿");
        set("long", @LONG
這裏是大堂旁邊的一個側殿，也是接待重要客人的地方。殿不
大，只擺放着一張桌子和幾把椅子。桌上擺放着一盆青山隱隱的盆
景，牆壁上掛着一些字畫。
LONG
        );
        set("exits", ([
                "south" : __DIR__"qingjing",
                "west" : __DIR__"piandian",
                "north" : __DIR__"datang3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/cheng" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -2780);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}