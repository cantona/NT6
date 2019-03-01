#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", NOR + RED "大棗樹上" NOR);
        set("long", @LONG
這裡是石窟內的一棵百仗高的大棗樹上，但見此處被樹葉
所蓋，密不透風。
LONG);
        set("exits", ([
              "up"    :  __DIR__"ontree3",
              "down"  :  __DIR__"ontree1",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
