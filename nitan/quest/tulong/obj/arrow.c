#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIC"鳳尾箭"NOR, ({ "fengwei jian", "arrow" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("value", 0);
                set("base_unit", "支");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "iron");
                set("long", "鳳尾箭連珠箭發，勢道兇猛。\n");
                set("wield_msg", HIC"$N迅速地從箭袋中抽出一束鳳尾箭，拉弦在手，就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的鳳尾箭放回箭袋中。\n"NOR);
        }
        set_amount(20);
        init_throwing(25);
        setup();
}
