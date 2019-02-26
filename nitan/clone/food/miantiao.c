// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

string *names = ({
  "刀削麪",
  "陽春麪",
  "細面",
  "鋼絲面",
  "雞絲麪",
  "牛肉絲麪",
  "蓋澆面",
  "滷味面",
  "排骨麪",
  "豆絲面",
  "羊雜碎面",
  "海鮮麪",
  "餛飩麪",
  "車仔麪",
  "肉煮麪",
  "長壽麪",
  "老家招牌面",
});

void create()
{
  set_name("各式麪條", ({"mian tiao", "miantiao", "mian"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一碗熱氣騰騰的麪條。\n");
    set("unit", "碗");
    set("value", 200);
    set("food_remaining", 5);
    set("food_supply", 35);
  }
}

void init()
{
  if (query("name")=="各式麪條")
    set_name(names[random(sizeof(names))], ({"mian tiao","miantiao","mian"}));
  ::init();
}