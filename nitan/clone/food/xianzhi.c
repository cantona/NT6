// 神話世界·西遊記·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// xianzhi.c        

inherit ITEM;
inherit F_LIQUID;

void create()
{
  string *names = ({
    "瓊漿",
    "玉液",
    "醍醐",
    "瑤露",
    });
  string *ids = ({
    "qiong jiang",
    "yu ye",
    "ti hu",
    "yao lu",
    });
  int i = random(4);

  set_name(names[i],({ids[i]}));
  set_weight(300);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "玉壺");
    set("value", 10000);
    set("max_liquid", 5000);
    set("no_get",1);
    set("no_drop",1);
    set("no_sell",1);
  }
  set("liquid", ([
        "type": "wine",
        "name": names[i],
        "remaining": 5000,
        "drunk_apply": 10,
     ]));
  set("long", "一玉壺天上才有的仙汁真酒－－"+names[i]+"。\n");
  setup();
}
