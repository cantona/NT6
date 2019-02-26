#include <ansi.h>

inherit ITEM;
int do_eat(string);
void init();

void init(){
  if (!wizardp(this_player())) {
    set("no_get","你手裏一鬆，內丹從指間滑落！\n");
    set("no_give","這麼珍貴的藥，哪能隨便給人？\n");
    set("no_drop","這麼寶貴的丹藥，扔了多可惜呀！\n");
    set("no_sell","凡人哪裏知道"+query("name", this_object())+"的價值？還是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}
void create(){
    set_name( HIY "內丹" NOR , ({"nei dan", "dan"}));
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

int do_eat(string arg){
  object me = this_player();
  if (arg!="dan" && arg!="nei dan")   return 0;

   addn("max_neili", random(30), me);
  addn("max_jing", random(30), me);
  addn("max_qi", random(30), me);
  addn("combat_exp", random(1000), me);
  message_vision(HIG "$N輕輕掰開一顆內丹送入嘴中，一時間香氣四溢。
只見$N臉慢慢變得通紅，好像非常痛苦的樣子，一會兒，\n 看起來充滿了力量！\n" NOR, me);
  destruct(this_object());
  return 1;
}
