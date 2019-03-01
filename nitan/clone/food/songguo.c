// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
// songguo.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("鬆果", ({"songguo"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一個黑色的鬆果．\n");
                set("unit", "個");
                set("food_remaining", 1);
                set("food_supply", 60);
        }
}
