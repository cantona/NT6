#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","你手裡一鬆，獎勵丹從指間滑落！\n");
    set("no_give","這麼珍貴的藥，哪能隨便給人？\n");
    set("no_drop","這麼寶貴的丹藥，扔了多可惜呀！\n");
  set("no_put","每個人只有一個，你都這麼大方！\n");
    set("no_sell","凡人哪裡知道"+this_object()->query("name")+"的價值？還是自己留著吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name( GRN "獎勵丹" NOR , ({"jiangli dan", "dan"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "顆");
    set("long", "一顆金黃色的丹丸，略微能聞到些許香氣。\n");
    set("value", 0);
    set("drug_type", "補品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="qn dan")   return 0;
  
 
   me->add("potential",300000);  
   me->add("daoxing",5000000);  
  message_vision(HIG "$N輕輕掰開一顆獎勵丹送入嘴中，一時間香氣四溢。
只見$N臉上慢慢泛出紅暈，看起來有精神多了！\n" NOR, me);
  destruct(this_object());
  return 1;
}

