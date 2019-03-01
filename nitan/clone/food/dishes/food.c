// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 

inherit ITEM;
inherit F_FOOD;

string *food_name= ({"麻辣肚絲",
                "鬆仁玉米",
     "梅菜扣肉",
     "五香臘腸",
     "魚香肉絲",
     "紅油雞片",
     "清炒蝦仁",
     "五花燜肉",
     "青絲熏魚",
     "糖醋排骨",
     "京醬肉絲",
     "油熗大蝦",
     "脆皮烤鴨",
     "紅燒素鵝",
     "宮保雞丁",
     "麻辣肚絲",
     "紅油肺片",
     "嫩汆豬肝",
     "走油脆腸",
     "爆炒腰花",
     "麝香冬筍",
     "翡翠豆腐",
     "麻婆豆腐",
     "三鮮腐竹",
});

void create()
{   string name = "婚禮大菜";
     set_name(name, ({"food"}));
     set_weight(1000);
     if (clonep())
         set_default_object(__FILE__);
     else {
         set("long", "一盤令人垂涎的婚禮大菜。\n");
         set("unit", "盤");
     set("eat_msg", "$N拿起玉筷夾了些" + name + "，放到嘴中吃了起來。\n");
         set("value", 250);
         set("food_remaining", 5);
         set("food_supply", 20);
     }
}

int do_get (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! arg)
    return 0;

  if (present(arg,environment(who))==me)
  {
    tell_object(who,"在婚禮上這麼幹似乎不大好吧！\n");
    return 1;
  }
  return 0;
}
