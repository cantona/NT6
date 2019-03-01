// zheshan.c
#include <weapon.h>

inherit DAGGER;

void create()
{
        set_name("油紙摺扇", ({ "zhe shan", "shan" }));
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("long", "這是一對用鑌鐵為骨的油紙摺扇。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲從懷中掏出一隻$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n揣回懷裏。\n");
        }
        init_dagger(15);
        setup();
}
