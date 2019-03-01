// pkp.c 撲克牌

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("撲克牌", ({ "pkp" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張普通的撲克牌，一般的賭徒都使用它。\n");
                set("value", 100);
                set("material", "paper");
                set("wield_msg", "$N「唰」的一聲抽出一張$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放回口袋。\n");
        }
        init_sword(25);
        setup();
}