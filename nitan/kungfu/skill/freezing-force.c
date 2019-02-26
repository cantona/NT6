// freezing-force.c 少林 冰蠶寒功
// Feb.21 1998 by Java

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "guixi-gong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("freezing-force", 1);
        return lvl * lvl * 22 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if( (!me->query_family() || 
            me->query_family() != "星宿派") && (!query("reborn/times", me) || member_array("星宿派", query("reborn/fams", me)) == -1) ) 
                return notify_fail("你不是星宿派門人，無法學習此神功。\n");

        if (me->query_skill("force", 1) < 50)
                return notify_fail("你的基本內功火候不夠，難以鍛鍊冰蠶寒功！\n");

/*
        if (me->query_skill("yijinjing", 1))
                me->delete_skill("yijinjing");
*/

        if (me->query_skill("force", 1) < me->query_skill("freezing-force", 1))
                return notify_fail("你的基本內功水平不夠，難以鍛鍊更深厚的冰蠶寒功！\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰蠶寒功無法通過簡單的練習來增加熟練度。\n");
}

// hit effect called by combatd
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        int lvl;
        int flvl;

        result = ::hit_ob(me, victim, damage_bonus, factor);
        if (intp(result) && result > 0)
        {
                lvl  = me->query_skill("freezing-force", 1);
                flvl=query("jiali", me);
                if (lvl < 80 || flvl < 10)
                        return;

                if (flvl * 2 + random(lvl) > victim->query_skill("force"))
                {
                        victim->affect_by("freezing",
                                ([ "level" : flvl * 3 / 2 + random(flvl / 2),
                                   "id":query("id", me),
                                   "duration" : lvl / 40 + random(lvl / 20) ]));

                        return ([ "damage" : result * 2,
                                  "msg" : HIW "霎時$n" HIW "只覺得寒風襲"
                                          "體，有種説不出的難受。\n" NOR ]);
                }
        }

        return result;
}

string exert_function_file(string func)
{
        return __DIR__"freezing-force/" + func;
}

string *fanzhen_msg = ({
        "只震得$N胸內腹中，有如五臟一齊翻轉！\n",
        "搶先反震，將$N震得臉如白紙，全無血色！\n",
        "震得$N心肺欲裂，騰騰騰連退數步！\n",
        "功力已佈滿全身，將$N的力量反震回去！\n",
        "震得$N天旋地轉，騰騰騰連退七八步！\n",
        "和$N一撞，只震的$p胸口氣血翻湧！\n",
        "$N便如撞在一堵棉花作面，鋼鐵為裏的厚牆上一般，震退數步！\n",
        "$N剛碰到$p，突然身子一震，登時飛了出去！\n",
});
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;
        
        if ((int) me->query_skill("freezing-force", 1) < 200 ||
            ! living(me))
                return;                      

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);
                        
                        msg = random(2) ? HIR "$n身上生出一股反震之力，" : HIR "$n身上冰蠶寒功隨心而起，";   
                              
                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;             
                
                        ob->receive_damage("qi", damage, me);
                        ob->receive_wound("qi", damage / 2, me);      
                        
                        result += ([ "msg" : msg ]);
                        
                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:  
                        case 1:
                        case 2:
                        case 3:                                                
                                result += ([ "msg" : HIR "好似有一堵無形的牆在$n面前阻擋着，結果"
                                                     "$N" HIR "一下子被反彈，震得$N" 
                                                     HIR "手臂發麻！\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "結果$n身上生出一股反震之力，$N只覺虎口一熱，" + 
                                                     weapon1->name() + HIR "頓時脱手而出，飛出丈外！\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}
