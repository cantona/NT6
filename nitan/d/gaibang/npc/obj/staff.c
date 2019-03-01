#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name(NOR + GRN "竹棒" NOR, ({ "zhu bang", "zhu", "bang" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", GRN "這是一根頗為破舊的竹棒，可以作為手杖使用。\n" NOR);
                set("unit", "根");
                set("material", "wood");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_staff(5);
        setup();
}