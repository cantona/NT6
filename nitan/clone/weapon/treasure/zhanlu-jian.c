// zhanlu-jian.c 湛盧劍
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIC"湛盧劍"NOR, ({ "zhanlu jian", "sword", "jian" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是春秋名匠歐冶子所鑄的五口寶劍之湛盧劍。\n");
                set("value", 100000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一聲抽出一口寒光閃閃的$n。劍面浮紋躍然閃動，實是一口難得的神兵。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(180);
        setup();
}