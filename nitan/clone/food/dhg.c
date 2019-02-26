// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// dhg.c 大黃瓜

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("大黃瓜", ({"dhg", "dahuanggua"}));
   set_weight(40);
   if (clonep())
     set_default_object(__FILE__);
   else {
                set("long", "一條新鮮嫩綠的大黃瓜。\n");
                set("unit", "條");
     set("value", 80);
     set("food_remaining", 4);
     set("food_supply", 30);
   }
}