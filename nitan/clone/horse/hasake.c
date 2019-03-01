inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "哈薩克馬" NOR, ({ "hasake ma"}));
        set("long", HIM "此馬產自內蒙古錫林郭勒地區，頗為強健。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}
