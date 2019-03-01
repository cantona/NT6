// Code of ShenZhou
// huxindan.c 天王護心丹
// xQin 04/01

#include <ansi.h>

inherit ITEM;
int cure_ob(string);
void create()
{
   set_name(RED"天王護心丹"NOR, ({"huxin dan", "tianwang dan", "dan"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("no_sell",1);
      set("no_get",1);
      set("no_drop",1);
      set("unit", "顆");
      set("value", 20000);
   }
   setup();
}


int cure_ob(object me)
{
   
   if (me->query_condition("hot_drug") > 0)
   {
   addn("max_neili", -1, me);
   message_vision(HIR"$N吃下一顆" + name() + HIR"，只覺五臟六腑都在絞痛，原來服食藥物過多，適得其反。\n"NOR, me);
   destruct(this_object());
   return 1;
   }
   set("eff_jing",query("max_jing",  me), me);
   set("jing",query("max_jing",  me), me);
   set("eff_qi",query("max_qi",  me), me);
   set("qi",query("max_qi",  me), me);

   
   message_vision(HIG"$N吃下一顆" + name() + HIG"，只覺全身舒泰，傷勢已大有好轉。\n"NOR, me);
   me->apply_condition("hot_drug", 20);
   destruct(this_object());
   return 1;
}