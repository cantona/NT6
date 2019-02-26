#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIY "炎龍神冠" NOR, ({ "yanlong shenguan", "shenguan", "yanlong" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一頂用龍角和龍鱗做成的頭冠。\n" NOR
                            HIC "有效招架修正：+ 10       有效輕功修正：  + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防禦效果等級：   10\n" NOR
                            HIC "抗毒迴避修正：+ 5%\n" NOR);
                set("unit", "頂");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIY "$N" HIY "輕輕地把$n"
                    HIY "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}