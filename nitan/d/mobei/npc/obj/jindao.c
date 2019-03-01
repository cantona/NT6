// Last Modified by winder on May. 25 2001
// jindao.c

#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(YEL"金刀"NOR, ({"jindao", "blade", "dao"}));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit","把");
                set("long","刀鞘是黃金所鑄,刀柄盡頭處鑄了一個黃金的虎頭,猙獰生威。\n");
                set("value", 5000);
                set("material","gold");
                set("wield_msg", "$N將$n抽出鞘來，只覺寒氣逼人，刃鋒上隱隱有血光之印。\n");
                set("unwield_msg", "$N將手中的$n插回黃金刀鞘。\n");
        }
        init_blade(60);
        setup();
}