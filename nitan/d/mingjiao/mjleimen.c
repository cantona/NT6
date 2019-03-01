// Room: /d/mingjiao/mjleimen.c
// Jan.5 1997 By Venus

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "青石地");
        set("long", @LONG
這是一片青石地，靜穆無塵。斜暉淡掃，石欄映日，輝影雪山。
三三兩兩高鼻深目，雪膚金髮男女教眾急步匆匆來去，所配兵器也非
中土能見。
LONG );
    set("exits", ([
        "southwest" : __DIR__"mjleimen1",
        "northeast" : __DIR__"mjsimen1",
    ]));
    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}