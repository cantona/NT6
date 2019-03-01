
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "智慧之冠" NOR, ({ "zhihui guan", "zhihui", "guan" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "gold");
                set("unit", "頂");
                set("long", HIR "這是一頂充滿智慧之光的頭冠，佩帶後可使冥思獎勵加倍。\n" NOR);
                set("value", 350000);
                set("armor_prop/int", 6);
                set("armor_prop/reflect2", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}