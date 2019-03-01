// Room: /d/mingjiao/nanshe.c
// Jan.5 1997 by Venus

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "天門男舍");
        set("long", @LONG
走進這間男舍，一陣汗臭酒熏撲面，根本揮趕不去。幾個五大三
粗漢子光腳神氣赳赳，豪邁異常地喊你入席。桌上酒水淋漓，杯盤狼
籍，顯然都喝得差不多了。
LONG );
    set("exits", ([
        "out" : __DIR__"mjtianmen1",
    ]));
    set("no_clean_up", 0);
    set("sleep_room", 1);
    set("no_fight", 1);
    setup();
    replace_program(ROOM);
}