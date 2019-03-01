#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIC "玉蜂針" NOR, ({ "yufeng zhen", "yufeng", "zhen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "這是一根細長的銀針，散發著淡淡的清香。\n" NOR);
                set("unit", "些");
                set("base_unit", "根");
                set("base_weight", 500);
                set("base_value", 0);
                set("material", "iron");
        }

        set_temp("daub/poison", ([
                "id"     : "xiao longnv",
                "remain" : 1000,
                "level"  : 80,
                "name"   : "玉蜂毒",
        ]));
        set_temp("daub/poison_type", "yufengdu");
        set_temp("daub/who_name", "小龍女");
        set_temp("daub/who_id", "xiao longnv");

        set_amount(50);
        init_throwing(50);
        setup();
}