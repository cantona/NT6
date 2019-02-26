// jiexue.c
// 衝開封閉的穴道

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再説吧！\n");

         force = me->query_skill("force");

         if (1)
         {
                if (! me->query_temp("fengxue"))
                      return notify_fail("你穴道並沒有封閉啊。\n");
          
                if (force < 300)
                      return notify_fail("你內功修為不足，無法將封閉的穴道衝開。\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("你內力修為不足，無法將封閉的穴道衝開。\n");

                message_vision(HIW "$N" HIW "暗運內功，一股真氣流至全身各處。\n" NOR, me);

                write(HIG "你周身被封閉的穴道已被衝開。\n" NOR);

                me->delete_temp("fengxue");
                me->set_temp("last_fengxue", time());
                me->start_busy(2);

                return 1;
         }    
}

int help(object me)
{
  write(@HELP
指令格式 : chongxue

該指令可以將被封閉的穴道衝開。
HELP
);
    return 1;
}
 
