// yubee.c

#include <condition.h>;
#include <ansi.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        object bee;
        string *msg=({
HIR"\n$N手舞足蹈地想捉住一隻"HIW"玉蜂"HIR"，可玉蜂一下子又飛開了。\n",
HIW"\n玉蜂"HIY"一會兒聚在一起，一會兒又散開，在$N頭上跳起舞來。\n",
HIW"\n玉蜂"HIC"忽然一下子都不見了，$N着急地想把他們找出來，卻怎麼也找不着。\n",
HIW"\n玉蜂"HIM"在飛舞！穿梭在飄香的花雨中，恍若來自天國的舞者，吸引着你的目光。\n",
        });
        if( !duration || !query_temp("marks/bee1", me) )
        {
                me->apply_condition("yubee", 0);
                return 0;
        }
        if(duration == 1)
        {
                me->reincarnate();
                message_vision(HIY"玉蜂嗡地一聲飛回蜂巢裏面。$N喜道：該去取蜜了。\n"NOR,me);
                set_temp("marks/bee1", 0, me);
//                bee=present("yu bee", environment(me));
//                destruct(bee);
                set_temp("marks/getmi", 1, me);
                set_temp("marks/mihave", 1, me);
                addn_temp("marks/mi", 1, me);
                return 0;
        }
//        if(me->query_temp("marks/bee1") && present("yu bee", environment(me)))
        {
                message_vision(msg[random(4)]+NOR,me);
        }
//        if(!present("yu bee", environment(me))) me->apply_condition("yubee", 0);
        me->apply_condition("yubee", duration - 1);
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "job";
}
