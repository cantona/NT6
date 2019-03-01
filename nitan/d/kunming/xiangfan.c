#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "廂房" );
        set("long", @LONG
一間不大的廂房，收拾的十分幹凈，看來是家人平是起居
之用，一扇小窗戶透進些光線了，顯的十分的舒心。
LONG);
        set("no_fight", 1);
        set("sleep_room", 1);
        set("exits", ([
                "west"   :__DIR__"dongzoulang1",
        ]));
        set("objects", ([
                "/d/shaolin/npc/shang1" : 2,
        ]));
	set("coor/x", -16810);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}