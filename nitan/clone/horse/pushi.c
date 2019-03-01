inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "普氏野馬" NOR, ({ "pushi yema"}));
        set("long", NOR + YEL "生活在新疆的普氏野馬一小時可奔跑六十公裡，還有連續奔跑四小時的耐力。\n" NOR);

    set("tili", 5000);
        set("max_tili", 5000);
        set("level", 2);

        setup();
}
