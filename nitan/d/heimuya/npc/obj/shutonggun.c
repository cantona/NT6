// shutonggun.c

#include <ansi.h>
#include <weapon.h>

inherit CLUB;

void create()
{
        set_name("熟銅棍", ({"shutong gun", "club"}));
        set_weight(2000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "一桿十分靈便的熟銅棍。\n");
                set("value", 1000);
                set("material", "bamboo");
                set("wield_msg", "$N回手從身後抽出一桿熟銅棍。\n");
                set("unwield_msg", "$N手往後一扣，把熟銅棍放在身後。\n");
        }
        init_club(30);
        setup();
}