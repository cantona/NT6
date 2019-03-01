// fuchen.c 
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("拂塵", ({ "fuchen" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long",
"這是一柄拂塵，做工精細，本來只是抹灰驅蠅的工具
後來成立道士手裡的道具，就漸漸失去原來的作用了。\n");
                set("value", 300);
                set("material", "leather");
                set("wield_msg",
"$N「唰」的一聲從頸中抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回頸中。\n");
        }
        init_whip(15);
        setup();
}
