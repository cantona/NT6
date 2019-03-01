// wanwutang.c 萬物堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "萬物堂");
        set("long", @LONG
這裏是全真七子之五王處一的居所。房間不大，收拾的素雅整
潔，牆上掛着一蕭一琴和一些字畫，小几上擺放着宣紙和徽墨狼毫，
不知道主人是要練字還是繪畫。
LONG
        );
        set("exits", ([
                "south" : __DIR__"huizhentang",
        ]));
        set("objects",([
                CLASS_D("quanzhen")+"/wangchuyi" : 1,
        ]));

        set("coor/x", -2800);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}