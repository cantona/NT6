// Room: /lingzhou/qingxinquan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "清新泉");
        set("long", @LONG
這是山中的一口清泉，位于林場北面的山坡上，周圍是翠綠的鬆樹，
潺潺的山泉水從泉眼緩緩的湧出，聚成一個小潭，小潭水又溢出流向山
下，旁邊一條小路通向山下。
LONG );
        set("exits", ([
                "southeast" : __DIR__"kongdi",
                "northdown" : __DIR__"wangling",
        ]));
        set("resource/water", 1);
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}