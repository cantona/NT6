#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "白虎筋" NOR, ({ "tiger vein", "vein" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一根白虎筋，乃製衣極品，世間罕有。可以將它系(wear)在腰間。\n" NOR
                            HIC "有效招架修正：+ 10        有效輕功修正：+ 10\n" NOR
                            HIC "抗毒效果修正：+ 3%        防禦效果等級：  10\n" NOR
                            HIC "抗毒迴避修正：+ 2%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 2);
                set("armor_prop/reduce_poison", 3);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "輕輕地把$n"
                    HIC "系在腰間。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
