#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
        set_name("束發金帶", ({ "jindai" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long","這是一條用金絲織成的束發帶子\n");
                set("value", 1500);
                set("material", "silk");
                set("armor_prop/armor", 1);
        set("female_only", 1);
        set("wear_msg", "$N將$n拿出束在頭發上。\n");
        }
        setup();
}
