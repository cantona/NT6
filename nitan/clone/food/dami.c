// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// chicken_leg.c

#include <weapon.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("一袋大米", ({"dami"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一袋大米，不過是生的．\n");
                set("unit", "袋");
                set("value", 200);
                set("food_remaining", 100);
                set("food_supply", 5);
                set("wield_msg", "$N抓起一袋大米，好像要和人拼命．\n");
     set("eat_msg", "$N拿出幾粒大米放到嘴裏嚼了嚼，差點把牙崩調！\n");
                set("material", "bone");
        }
        setup();
}

