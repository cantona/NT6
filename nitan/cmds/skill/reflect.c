// reflect.c
// 冥思指令獲取少量經驗和潛能
// 會員專用指令 Create by Rcwiz for HERO.CD

#include <ansi.h>
#define MEMBER_D     "/adm/daemons/memberd"

inherit F_CLEAN_UP;

void end_reflect(object me)
{
         mixed exp, pot;

         if( query_temp("reflect", me) )
         {
               message_vision(HIY "$N" HIY "冥思完畢，緩緩地睜開眼睛，似乎若有所悟！\n" NOR, me);
 
               delete_temp("reflect", me);

               exp=query("combat_exp", me);
               exp /= 100000;
               if (exp > 2000) exp = 2000;
               pot = exp / 5;

               exp = exp + random(exp / 2);
               pot = pot + random(pot / 2);
               if( query("jingmai/reflect", me) )
               {
                       exp+=exp*query("jingmai/reflect", me)/100;
                       pot+=pot*query("jingmai/reflect", me)/100;
               }

               addn("combat_exp", exp, me);
               addn("potential", pot, me);

               write(HIG "通過這次冥思，你獲得了" HIC + chinese_number(exp) + HIG 
                     "點實戰經驗和" HIC + chinese_number(pot) + HIG "點潛能。\n");

         }

         if (! me->is_busy())me->start_busy(1);
         return;
}

int main(object me)
{
         object ob;


         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再說吧！\n");

         if( query_temp("reflect", me) )
                 return notify_fail("你正在冥思。\n");

         if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me)))
                 return 0;

         if( !query("doing", me) )
                 return notify_fail("只有計劃時才能冥思。\n");

         if( query("combat_exp", me)<1000000 )
                  return notify_fail("你實戰經驗，無法冥思。\n");

         if (me->query_skill("martial-cognize", 1) < 160)
                  return notify_fail("你武學修養不足，無法冥思。\n");
 

         set_temp("reflect", 1, me);

         me->start_busy(30);

         me->start_call_out((: call_other, __FILE__,
                             "end_reflect", me:), 28 + random(6));

         message_vision(HIY "$N" HIY "盤膝而坐，閉目冥思 ……\n" NOR, me);

         return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : reflect

該指令可以在計劃時使用以提高少量經驗和潛能。
該指令只限會員使用。

HELP
);
    return 1;
}
 
