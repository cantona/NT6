#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "小房間");
        set("long", @LONG
這是一個小房間，桌上點著蠟燭。房中只有一桌一床，陳設簡單，
卻十分幹凈。床上舖著被褥。
LONG );
    set("exits", ([
                "south" : "/d/beijing/zhuang8",
    ]));
    set("objects", ([
        "/d/beijing/npc/furen": 1,
          "/d/beijing/npc/shuanger": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4740);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}