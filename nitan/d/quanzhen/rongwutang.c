// rongwutang.c 容物堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "容物堂");
        set("long", @LONG
這裡是全真七子之二譚處端的居室，這間房間收拾的和普通的民
居沒什麼區別，只是一塵不染，牆上斜掛著一把寶劍。
LONG
        );
        set("exits", ([
                "north" : __DIR__"xianzhentang",
        ]));
        set("objects",([
                CLASS_D("quanzhen")+"/tan" : 1,
        ]));
        set("coor/x", -2800);
        set("coor/y", 90);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}