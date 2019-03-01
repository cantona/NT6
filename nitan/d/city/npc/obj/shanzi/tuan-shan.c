#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(HIC "團扇" NOR, ({ "tuan shan", "tuan", "shan" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIC "這是一把用上好絹絲制作的團"
                            "宮，繡著精細的花鳥。\n" NOR);
                set("value", 3000);
                set("material", "wood");
                set("wield_msg", "$N拿起一把$n握在手裡。\n");
                set("unwield_msg", "$N合上$n，收回懷裡。\n");
        }
        init_dagger(15);
        setup();
}
