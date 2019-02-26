#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "衡山派客房");
        set("long", @LONG
這是一間很大的客房，是衡山派供前來祭神的遊客暫住的房間陳
設十分簡陋。 靠牆放了十幾張小木牀。 雖然簡陋了點但是總比在荒
山中露宿強得多了。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([
               "south" : __DIR__"changlang",
        ]));
	set("coor/x", -6920);
	set("coor/y", -5480);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}