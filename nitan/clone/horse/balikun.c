inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "巴里坤馬" NOR, ({ "balikun ma"}));
        set("long", HIC "巴里坤馬是“神馬“（胭脂馬）的後代，體型矮小，但速度極快。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}
