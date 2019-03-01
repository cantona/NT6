// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

string *names = ({
  "刀削面",
  "陽春面",
  "細面",
  "鋼絲面",
  "雞絲面",
  "牛肉絲面",
  "蓋澆面",
  "鹵味面",
  "排骨面",
  "豆絲面",
  "羊雜碎面",
  "海鮮面",
  "餛飩面",
  "車仔面",
  "肉煮面",
  "長壽面",
  "老家招牌面",
});

void create()
{
  set_name("各式面條", ({"mian tiao", "miantiao", "mian"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一碗熱氣騰騰的面條。\n");
    set("unit", "碗");
    set("value", 200);
    set("food_remaining", 5);
    set("food_supply", 35);
  }
}

void init()
{
  if (query("name")=="各式面條")
    set_name(names[random(sizeof(names))], ({"mian tiao","miantiao","mian"}));
  ::init();
}