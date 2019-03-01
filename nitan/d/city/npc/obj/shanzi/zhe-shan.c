#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(NOR + WHT "折扇" NOR, ({ "zhe shan", "zhe", "shan" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", NOR + WHT "這是一把做工精巧的紙面折扇。\n" NOR);
                set("value", 1000);
                set("material", "wood");
                set("wield_msg", "$N拿起一把$n握在手裡。\n");
                set("unwield_msg", "$N合上$n，收回懷裡。\n");
        }
        init_dagger(15);
        setup();
}