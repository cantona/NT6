// drunk.c
#include <combat.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

  if (me->is_ghost()) return 1;
        if( !living(me) ) {
                message("vision", me->name() + "身上的傷口尚未痊癒, 但是覺得似乎油盡燈枯了!!\n",
                        environment(me), me);
        } else if( duration > 20 ) {
                tell_object(me, "你的傷口似乎很嚴重, 血流不止.\n");
                message("vision", me->name() + "身上的傷口血流如注, 顯然受傷十分嚴重. \n",
                        environment(me), me);
                me->receive_wound("qi", 20,"傷勢過重");
        } else if( duration > 10 ) {
                tell_object(me, "你覺得身上的傷口開始密合了, 血流量也變少了. \n");
                message("vision", me->name() + "似乎受傷不輕, 身上血跡班班. \n",
                        environment(me), me);
                me->receive_wound("qi", 10,"傷勢過重");
        } else if( duration > 5 ) {
                tell_object(me, "你身上的傷口開始結疤了, 也感覺不到痛苦了. \n");
                message("vision", me->name() + "的身上有一道新疤, 好像受到不輕的傷害. \n",
                        environment(me), me);
                me->receive_wound("qi", 5,"傷勢過重");
        }
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("bleeding", duration - 1);
//        COMBAT_D->report_status(me, 1);
        if( !duration )
                 return 0;
        return 1;
}