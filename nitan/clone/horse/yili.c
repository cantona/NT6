inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "伊犁馬" NOR, ({ "yili ma"}));
        set("long", HIC "此馬產自新疆伊犁，乃烏孫馬的後代，腳力甚好，有“天馬”之稱。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}
