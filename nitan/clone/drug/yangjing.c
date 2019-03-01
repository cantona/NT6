// Code of ShenZhou
#include <ansi.h>

inherit ITEM;
int cure_ob(string);
void create()
{
   set_name("養精丹", ({"yangjing dan", "dan"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("unit", "粒");
      set("value", 100);
                set("no_sell", 1);
      set("medicine", 1);
   }
   setup();
}

int cure_ob(object me)
{
   message_vision("$N吃下一粒" + name() + "。\n", me);
   if ((int)me->query_condition("xx_poison") > 50){
   tell_object(me, "你中毒太深，此藥沒什麼效。\n");
   destruct(this_object());
   return 1;
   }

   if( query("eff_jing", me)<query("max_jing", me)){
      me->apply_condition("jing_curing", me->query_condition("jing_curing")
         + 10);
   }

   destruct(this_object());
   return 1;
}