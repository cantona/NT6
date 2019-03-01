#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIR "聖靈腰帶" NOR, ({ "shengling belt", "belt", "shengling" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一根閃耀著奇異光芒的腰帶。\n" NOR) ;
                set("unit", "根");
                set("value", 400000);
                set("armor_prop/armor", 100);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
