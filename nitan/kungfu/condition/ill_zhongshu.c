// ill_zhongshu.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_zhongshu"; }

int min_qi_needed() { return 15; }

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;

        message("vision", HIG + me->name() + "頭重腳輕，暈暈乎乎抬不"
                          "起頭來，看來是中暑了。\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 2 ) {
                me->set_temp("die_reason", "中暑太深，暴斃身亡了");
                me->die();
                return 0;
        }
        else
        tell_object(me, HIB "你覺得胸臆之間一陣翻騰，頭重"
                        "腳輕，腦門發熱，看來是中暑了。\n" NOR );

        me->receive_wound("qi", 2);
        me->receive_damage("qi", 2);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}
