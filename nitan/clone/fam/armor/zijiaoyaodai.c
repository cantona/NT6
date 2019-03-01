#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(NOR + MAG "紫蛟腰帶" NOR, ({ "zijiao belt", "belt", "zijiao" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一根用南海惡蛟之筋做成的腰帶，隱隱地透著邪氣。\n" NOR
                            HIC "有效招架修正：+ 15        有效輕功修正： + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%        防御效果等級：  40\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 40);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 5);
                set("armor_prop/parry", 15);
                set("wear_msg", NOR + MAG "$N" NOR + MAG "輕輕地把$n"
                    NOR + MAG "系在腰間。\n" NOR);
                set("remove_msg", HIC "$N" HIC "輕輕地把$n"
                    HIC "從腰間取了下來。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}