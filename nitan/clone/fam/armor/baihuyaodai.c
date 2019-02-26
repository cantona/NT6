#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "白虎腰帶" NOR, ({ "baihu belt", "belt", "baihu" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一根用神獸白虎之筋做成的腰帶，虎虎生威，令人不敢貿然接近。\n" NOR
                            HIC "有效招架修正：+ 10        有效輕功修正：+ 10\n" NOR
                            HIC "抗毒效果修正：+ 5%        防禦效果等級：  40\n" NOR
                            HIC "抗毒迴避修正：+ 5%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 40);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "輕輕地把$n"
                    HIW "系在腰間。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}