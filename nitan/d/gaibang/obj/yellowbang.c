//Cracked by Kafei
//yellowbang.c 黃竹棒
#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("黃竹棒", ({ "huang zhubang", "bang", "zhu bang", "zhubang", "staff", "yellow staff" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這根竹棒雖不如打狗棒堅韌，長短輕重卻是一般無異，只是色作淡黃，以示與打狗棒有別。\n");
                set("rigidity", 2000);
                set("value", 1000);
                set("material", "bamboo");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_staff(50);
        setup();
}
