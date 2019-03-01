// fengxue.c
// 封閉穴道防止毒氣擴散和發作

#include <ansi.h>

inherit F_CLEAN_UP;

void end_fengxue(object me)
{
         if (me->query_temp("fengxue"))
         {
               write(HIG "你長舒一口氣，周身被封閉的穴道已自動解開。\n");
 
               me->delete_temp("fengxue");

               me->set_temp("last_fengxue", time());        
         }

         return;         
}

// 還要添加set fengxue 1

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再說吧！\n");


         if (time() - me->query_temp("last_fengxue") < 60)
                 return notify_fail("你的穴道剛沖開，不能繼續封穴了。\n");

         force = me->query_skill("force");
/*
         if (me->query_skill("jingluo-xue", 1) < 100)
                  return notify_fail("你對經絡學了解不夠，無法封穴。\n");
*/
         if (! arg)
         {
                if (me->query_temp("fengxue"))
                      return notify_fail("你已經將周身要穴封閉。\n");                
          
                if (force < 300)
                      return notify_fail("你內功修為不足，無法將自己穴道封閉。\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("你內力修為不足，無法將自己穴道封閉。\n");

                message_vision(HIW "$N" HIW "暗運內息，右手食指猛地點向周身各"
                               "處，將要穴封閉。\n" NOR, me);

                me->set_temp("fengxue", 1);

                me->start_busy(2);

                me->start_call_out((: call_other, __FILE__,
                               "end_fengxue", me:), force / 5);

                return 1;                
         }    
         
         if( !objectp(ob = present(arg, environment(me))) )
		 return notify_fail("這裡沒有 " + arg + "。\n");
         
         if (! playerp(ob))
                 return notify_fail("你只能幫助玩家封穴。\n");

         if (! ob->query("env/fengxue") || ob->query_temp("fengxue"))
                 return notify_fail("對方現在不需要你幫助封穴。\n");

         if (force < 400)
                 return notify_fail("你內功修為不足，無法幫助其他玩家封穴。\n");

         if (me->query("neili") < 300)
                 return notify_fail("你內力不足，無法幫助其他玩家封穴。\n");

         if (me->query("max_neili") < 3000)
                 return notify_fail("你內力修為不足，無法幫助其他玩家封穴。\n");

         message_vision(HIY "$N" HIY "將內力運于指間，猛地點向$n" HIY "周"
                        "身各處，將其要穴封閉。\n" NOR, me, ob);

         ob->set_temp("fengxue", 1);

         ob->start_busy(2);
         me->start_busy(2);
         me->add("neili", -220);

         me->start_call_out((: call_other, __FILE__,
                           "end_fengxue", ob:), force / 5);
         return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : fengxue [玩家ID]

該指令可以在中毒時暫時將穴道封閉，以免毒性發作。
當穴道沖開後一分鐘內不能再繼續封穴。

HELP
);
    return 1;
}
 
