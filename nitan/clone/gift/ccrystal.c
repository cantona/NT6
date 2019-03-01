// ccrystal.c 水晶殘片

#include <ansi.h>
#include <armor.h>

inherit HEAD;

int is_enchase_ob(){ return 1; }

void create()
{
        set_name(HIM "水晶殘片" NOR, ({ "chipped crystal" }) );
        set_weight(25);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一片粉色的水晶碎片。\n" NOR);
                set("value", 20000);
                set("unit", "片");
                set("armor_prop/per", 3);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從頭上摘了下來。\n" NOR);
        }
        setup();
}
