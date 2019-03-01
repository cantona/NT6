// chanfang3.c 禪房
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "禪房");
        set("long", @LONG
這裡是全真弟子修身養性、打熬氣力的地方。為了方便練功，桌
椅都沒有擺放，僅僅在地下丟了幾個小蒲團。
LONG
        );
        set("exits", ([
                "east" : __DIR__"xiaohuayuan2",
                "west" : __DIR__"chanfang2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2730);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}