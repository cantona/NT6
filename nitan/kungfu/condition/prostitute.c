// prostitute.c
#include <condition.h>
#include <ansi.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if (duration < 1) return 0;
   if (file_name(environment(me))!="/d/city/lichunyuan2")
   {
   tell_object(me,HIY"麗春院龜公出現在你身邊：你能跑哪裡去！快回去接客！\n"NOR);
      message_vision(CYN"麗春院龜公突然出現，不由分說，拉了$N就走。\n"NOR,me);
      me->move("/d/city/lichunyuan2");
   }
   me->apply_condition("prostitute", duration - 1);
   return CND_CONTINUE;
}
