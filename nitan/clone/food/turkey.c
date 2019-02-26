// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 

inherit ITEM;
inherit F_FOOD;

string *names= ({
  "脆烤火雞",
  "香薰火雞",
  "填棗火雞",
});

string *parts= ({
  "火雞肉",
  "火雞小腿肉",
  "火雞大腿肉",
  "火雞翅膀肉",
  "火雞背板肉",
  "火雞脯子肉",
  "火雞頸子肉",
  "火雞屁股肉",
  "火雞頭",
  "火雞胗",
  "火雞肝",
  "火雞腸",
  "火雞皺腸",
  "火雞針線包腰子",
  "火雞枕頭肺",
  "火雞肋骨",
  "火雞頸骨",
  "火雞翅骨",
  "火雞腿骨",
});

void create()
{
  string name = "火雞";
  set_name(name, ({"turkey"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一隻碩大的感恩節火雞。\n");
    set("unit", "只");
    set("value", 950);
    set("food_remaining", 30);
    set("food_supply", 10);
  }
  setup();
}

int do_get (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! arg)
    return 0;

  if (present(arg,environment(who))==me)
  {
    tell_object(who,
     "喂！過節讓大家吃火雞嘛，您瞧您，鬼鬼祟祟賊頭賊腦的樣子！\n");
    return 1;
  }
  return 0;
}
