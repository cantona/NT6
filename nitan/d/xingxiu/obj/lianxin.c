//Cracked by Roath
#include <ansi.h>

inherit ITEM;
int throw_ob(object me, object victim);
void create()
{
   set_name(RED"煉心彈"NOR, ({"lianxin dan", "dan", "lianxin"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("unit", "顆");
      set("long", RED"一顆硫磺硝磷所制的火彈，內夾毒藥。\n" NOR);
      set("skill", "feixing-shu");
      set("value", 0);
   }
   setup();
}

int throw_ob(object me, object victim)
{
        int ap, dp;

   message_vision(BLU"$N一揚手，衣袖中飛出一點藍印印的火花，如一只飛螢，向$n撲過去。\n" NOR, me, victim);
   ap = me->query_skill("feixing-shu", 1);
   dp = (int)victim->query_skill("dodge");
   ap*=query("combat_exp", me)/1000;
   dp*=query("combat_exp", victim)/1000;
   
   ap = random(ap);
        
        if (ap > dp/2){
   message_vision(RED"只聽見一陣嗤嗤聲響，那飛螢已落在$n的肩頭，把$n的肩部燒得焦爛。\n" NOR, me, victim);
   me->improve_skill("feixing-shu", 1);
   victim->apply_condition("insect_poison", 12);
   set("poisoner", me, victim);
   victim->receive_wound("qi", 100);
   victim->receive_wound("jing", 50);
   if( !victim->is_killing(me) ) victim->kill_ob(me);
   me->start_busy(1+random(3));
   if( query("combat_exp", victim)>query("combat_exp", me)){
         addn("combat_exp", 5+random(5), me);
        me->improve_skill("feixing-shu",query("int", me));
   }
   destruct(this_object());
   return 1;
   }
   else
        {
        message_vision("$n發現不妙，趕緊向後躍開數丈，躲了開去。\n" NOR, me, victim);
        if( !victim->is_killing(me) ) victim->kill_ob(me);
        me->start_busy(1+random(3));
        destruct(this_object());
        }
        return 1;
}    