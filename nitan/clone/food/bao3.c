// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
// dumpling.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("素菜餡包子", ({"sucai bao", "bao"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一個香噴噴、熱騰騰的素菜餡灌湯包子。\n");
                set("unit", "個");
                set("value", 25);
                set("food_remaining", 2);
                set("food_supply", 40);
        }
}
