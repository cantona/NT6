// cetang.c 側堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "側堂");
        set("long", @LONG
這裏是大堂旁邊的一個側廳，也是接待重要客人的地方。廳不
大，只擺放着一張桌子和幾把椅子。桌上擺放着一盆青松山石的盆
景，牆壁上掛着一些字畫。
LONG
        );
        set("exits", ([
                "east" : __DIR__"guozhendian",
                "west" : __DIR__"huizhentang",
                "north" : __DIR__"shiweishi",
                "south" : __DIR__"datang2",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/li" : 1,
        ]));

        set("coor/x", -2790);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}