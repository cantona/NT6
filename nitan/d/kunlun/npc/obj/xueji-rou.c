// Room: /d/kunlun/npc/obj/xueji-rou.c 雪雞肉
// Last Modified by winder on Jun. 29 2001

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("雪雞肉", ({"xueji rou", "rou"}));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻又肥又白的雪雞肉。\n");
                set("unit", "塊");
                set("food_remaining", 3);
                set("food_supply", 40);
        }
}