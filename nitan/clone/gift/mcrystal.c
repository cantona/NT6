// mcrystal.c 神之水晶

#include <ansi.h>
#include <armor.h>

inherit HEAD;

int is_enchase_ob(){ return 1; }

void create()
{
        set_name(HIM "神之水晶" NOR, ({ "magic crystal" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一塊閃爍這奇異光芒的粉色水晶，"
                    "讓人感到一陣陣的心悸。\n" NOR);
                set("value", 200000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 15 + random(16));
                set("armor_prop/per", 8);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從頭上摘了下來。\n" NOR);
        }
        setup();
}
