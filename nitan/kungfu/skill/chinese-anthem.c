// chinese-anthem.c 義勇軍進行曲

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa" ||
                                        usage == "tanqin-jifa" ||
                                        usage == "guzheng-jifa"; }

int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( query("jing", me)<80 )
                return notify_fail("你的精神不夠好，沒法練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你現在實在是太累了。\n");

        me->receive_damage("jing", 50);
        me->receive_damage("qi", 50);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        object attacker;
        object target;
        string msg;
        int lvl;
        int i;

        lvl = me->query_skill("chinese-anthem", 1);

        if (lvl < 200) return;
        
        // special effort
        target = 0;
        attacker = 0;
        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                if (obs[i] == me || ! living(obs[i]))
                        continue;

                if (obs[i]->is_fighting() && (target = obs[i]->query_competitor()) &&
                    query("nation", target) == "日本" )
                {
                        attacker = obs[i];
                        break;
                }
        }

        message("vision", HIY "你聽了這首慷慨激昂的國歌，不禁激"
                "動萬分，説不出的興奮。\n" NOR, obs, ({ me }));
        tell_object(me, HIY "你演奏完了這首慷慨激昂的國歌，不禁激"
                "動萬分，説不出的興奮。\n" NOR);
        if (attacker)
        {
                if( query("gender", attacker) == "女性" )
                        msg = HIR "\n一時間$N" HIR "不覺是心潮澎湃，不能"
                              "自已，杏目圓睜，口中一聲嬌喝：“倭賊！受死吧！”\n" NOR;
                else
                        msg = HIR "\n一時間$N" HIR "不覺是熱血沸騰，對$n"
                              HIR "大喝道：“東洋倭賊，還不受死？”\n" NOR;
                message_vision(msg, attacker, target);
                
                i = (lvl - 200) / 10;
                if (i > 10) i = 10;
                while (i--)
                        COMBAT_D->do_attack(attacker,target,query_temp("weapon", attacker),0);
        }
}