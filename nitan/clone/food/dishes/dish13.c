// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  string name = "嫩汆豬肝";
  set_name(name, ({"nenqiang zhugan", "zhugan", "gan"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一盤令人垂涎的"+name+"。\n");
    set("unit", "盤");
    set("value", 250);
    set("food_remaining", 5);
    set("food_supply", 25);
  }
}