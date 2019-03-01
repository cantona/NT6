// Jay May 27, 96

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("綢帶", ({ "whip" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long", "這是一條素色的綢帶，是舞蹈時的道具。\n");
                set("value", 300);
                set("material", "cloth");
                set("wield_msg", "$N淺笑嫣然，右手輕揚，舞出一條$n。\n");
                set("unwield_msg", "$N將手中的$n繞在腰間。\n");
        }
        init_whip(40);
        setup();
}
