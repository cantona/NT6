#include <weapon.h>

inherit SWORD;
#include <ansi.h>

void create()
{
        set_name(HIR"越女"+HIY"朝陽"+HIC"劍"NOR, ({ "yuenv chaoyang jian", "yuenv jian","jian", "sword" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("weapon_prop/kar", 15);
                set("weapon_prop/int", 3);
                set("weapon_prop/str", 5);
                set("weapon_prop/sword", 50);
                set("unit", "把");
                set("value", 10000000);
                set("material", "steel");
                set("long", "一把赤紅軟劍，據說是戰國時越女的隨身佩劍，其鋒利程度不下幹將 莫邪。\n");
                set("wield_msg", HIR"一聲脆響,$N手裡無聲無息的多了把赤紅軟劍.\n"NOR);
                set("wield_msg", HIR"空氣突然變得沉悶..,但聽...\n"
                                 HIB"鏘........鏹........嗆................\n"
                                 HIY"陣陣清越龍吟聲不斷響起...連綿不絕,$N手裡已多了把"HIR"赤紅軟劍.\n"NOR);
        }

        init_sword(500,2);
        setup();
}

int query_autoload() { return 1; }

