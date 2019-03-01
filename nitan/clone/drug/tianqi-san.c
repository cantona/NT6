// Code of HUAXIA
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "田七鯊膽散" NOR, ({"tianqi san", "san"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "：這是一包田七鯊膽散，可解化屍粉毒。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
   if (!me->query_condition("hsf_poison"))
   {
      tell_object(me, "你又沒中化屍粉毒，亂吃藥幹嘛？\n");
      return 1;
   }

   message_vision("$N吃下一包" + name() + "。\n", me);
   tell_object(me, "你覺得嘴裡非常的苦。\n");

   if ((int)me->query_condition("hsf_poison") < 100) {
      me->clear_condition("hsf_poison");
      tell_object(me, "你覺得傷口不再疼痛，化屍粉毒已經解除了。\n");
   } else if ((int)me->query_condition("hsf_poison") >= 100)
   {
      me->apply_condition("hsf_poison",(int)me->query_condition("hsf_poison")-90);
      tell_object(me, "你覺得好受了一點，不過化屍粉毒還沒有完全消除。\n");
   }

   destruct(this_object());
   return 1;
}
