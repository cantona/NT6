// leizhendang.c

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name("雷震擋", ({"leizhen dang", "staff"}));
        set_weight(8000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "一桿十分沉重的雷震擋。\n");
                set("value", 10000);
                set("material", "bamboo");
                set("wield_msg", "$N回手從身後抽出一桿雷震擋。\n");
                set("unwield_msg", "$N手往後一扣，把雷震擋放在身後。\n");
        }
        init_staff(35);
        setup();
}