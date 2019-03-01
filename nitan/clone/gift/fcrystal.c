// fcrystal.c 稀世水晶

#include <ansi.h>
#include <armor.h>

inherit HEAD;

int is_enchase_ob(){ return 1; }

void create()
{
        set_name(HIM "稀世水晶" NOR, ({ "flawless crystal" }) );
        set_weight(40);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一塊光彩照人的大水晶，美侖"
                            "美奐，世所罕有。\n" NOR);
                set("value", 100000);
                set("unit", "塊");
                set("armor_prop/per", 7);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從頭上摘了下來。\n" NOR);
        }
        setup();
}
