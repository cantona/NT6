// Room: /d/mingjiao/mjtianmen.c
// Jan.5 1997 By Venus

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "黃土地");
        set("long", @LONG
這是一片黃土地，塵沙泛起，劍芒凌空，刀槍晃日，殺氣盈野，
幾個小夥子膀大腰圓，一身短打，練功不掇。到此地，便能感覺到明
教百年興旺的根柢非虛。
LONG );
    set("exits", ([
        "northwest" : __DIR__"mjtianmen1",
        "southeast" : __DIR__"mjsimen1",
    ]));
    set("objects", ([
        "/clone/npc/mu-ren": 4,
    ]));
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}