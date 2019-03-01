#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(HIW"珍珠"HIC"甲魚"HIY"湯"NOR, ({"zhenzhu soup"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是“四季美飯莊”的一道名菜，香噴噴地冒著熱氣。\n");
                set("unit", "碗");
                set("value", 1000);
                set("max_liquid", 50);
              }
                set("liquid", ([
                    "name" : HIW"珍珠"HIC"甲魚"HIY"湯"NOR,
                    "remaining" : 10,
                    "type" : "water"
                ]) );
                set("liquid_type", "water");
                setup();
}