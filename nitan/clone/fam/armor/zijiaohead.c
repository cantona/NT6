#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(NOR + MAG "紫蛟頭顱" NOR, ({ "yanlong shenguan", "shenguan", "yanlong" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一頂用蛟龍角和蛟龍皮革做成的紫蛟模樣頭冠。\n" NOR
                            HIC "有效招架修正：+ 10       有效輕功修正：  + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防御效果等級：   10\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "頂");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", NOR + MAG "$N" NOR + MAG "輕輕地把$n"
                    NOR + MAG "戴在頭上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}