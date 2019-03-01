inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIB "黑風" NOR, ({ "hei feng"}));
        set("long", HIB "一匹渾身黝黑的馬，看起來很能跑。\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}
