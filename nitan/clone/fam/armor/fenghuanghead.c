#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "鳳凰頭冠" NOR, ({ "fenghuang touguan", "touguan", "fenghuang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "一頂用火鳳凰羽毛和鳳凰角做成的頭冠，透射出一道攝人心魄的光芒。\n" NOR
                            HIC "有效招架修正：+ 10        有效輕功修正： + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防禦效果等級：  10\n" NOR
                            HIC "抗毒迴避修正：+ 5%\n" NOR);
                set("unit", "頂");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 5);
                set("armor_prop/parry", 10);
                set("wear_msg", HIR "$N" HIR "輕輕地把$n"
                    HIR "戴在頭上，剎那間光華四射。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}