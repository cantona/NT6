// tiejiang.c
#include <weapon.h>
#include <ansi.h>
inherit CLUB;

void create()
{
        set_name("鐵槳", ({ "tie jiang", "jiang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根鐵槳，舉可齊眉，看來很是沉重，可攻擊大片敵人。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_club(30);
        setup();
}
