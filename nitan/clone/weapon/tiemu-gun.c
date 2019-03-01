#include <ansi.h>
#include <weapon.h>
inherit CLUB;

void create()
{
        set_name(HIG "鐵木棍" NOR, ({ "tiemu gun", "gun" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", HIG "這是一根用千年鐵木所鑄造的棍子，威力非凡。\n" NOR);
                set("material", "wood");
                set("value", 600000);
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_club(500);
        setup();
}

int query_autoload()
{
        return 1;
}
