// huizhentang.c 會真堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "會真堂");
        set("long", @LONG
這裡是大堂旁邊的一個側廳，也是接待重要客人的地方。廳不
大，只擺放著一張桌子和幾把椅子。桌上擺放著一盆青鬆山石的盆
景，牆壁上掛著一些字畫。
LONG
        );
        set("exits", ([
                "east" : __DIR__"cetang",
                "north" : __DIR__"wanwutang",
                "south" : __DIR__"datang1",
        ]));
        set("objects",([
                CLASS_D("quanzhen")+"/cui" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2800);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}