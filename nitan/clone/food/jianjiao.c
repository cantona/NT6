// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("素煎餃", ({"jian jiao", "jiao", "dumpling"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一盤嫩黃脆皮的素煎餃。\n");
    set("unit", "盤");
    set("value", 200);
    set("food_remaining", 5);
    set("food_supply", 35);
  }
}