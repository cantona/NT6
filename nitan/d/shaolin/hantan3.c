// Room: /d/shaolin/hantan3.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "萬古寒潭");
        set("long", @LONG
這是寒潭之中。冰與水混合在一起，使整個潭水在此處變得跟稀
粥一樣，身周的冰殼已凝成一個大塊，除了雙眼尚能透過冰層視物外，
全身各處都已動彈不得，只能聽任水流帶你繼續往下沉去。
LONG );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}