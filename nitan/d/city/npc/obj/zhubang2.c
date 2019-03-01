// zhubang2.c 竹棒
// 可以賣的竹棒，2兩銀子

#include <weapon.h>
inherit STICK;

void create()
{
        set_name("竹棒", ({ "zhubang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根做工精致的竹棒，棒端用細帆布包裹，以免誤傷同伴。\n");
                set("value", 2000);
                set("material", "bamboo");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_stick(1);
        setup();
}
 