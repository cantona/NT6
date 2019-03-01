#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIM "雷神之瞳﹒電" NOR, ({"leishen tong", "leishen", "tong"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "頃刻間，七彩之光透射天地，此乃天界之聖物，擁有著神一般的力量。\n" NOR);
                set("unit", "顆");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("enchase/cur_firm", 100); 
                set("enchase/type", "all");
                set("enchase/SN", 1 + random(9));
                set("enchase/weapon_prop", ([
                        "add_lighting" : 50,     
                        "add_skill" : 30,     
                ]));
                set("enchase/armor_prop", ([
                        "add_lighting" : 50,     
                        "add_skill" : 30,     
                ]));
                set("magic/type", "lighting");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
