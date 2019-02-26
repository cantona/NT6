// edit by gladiator

#include <ansi.h>

inherit SHAOLIN_SKILL;

mapping *action = ({
([     "action": HIG"$N將$w"HIG"抖動成圓，一式「圓轉如意」，$w"HIG"已將$n$l纏住"NOR,
       "dodge": 50,
       "damage": 100,
       "force":  300,
       "lvl" : 30,
       "skill_name" : "圓轉如意",
       "damage_type":  "拉傷"
]),
([     "action": HIW"$N的$w"HIW"在$n身旁連連進擊，忽然一招「佛自西來」從$n$l處倒捲上來"NOR,
       "dodge": 50,
       "damage": 150,
       "force": 400,
       "lvl" : 60,
       "skill_name" : "佛自西來",
       "damage_type":  "拉傷"
]),
([     "action": HIM"$N運起少林真氣，$w"HIM"陡然變成筆直，一式「佛坐蓮花」，向$n直刺過去"NOR,
       "dodge": 50,
       "damage": 180,
       "force": 450,
       "lvl" : 90,
       "skill_name" : "佛坐蓮花",
       "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;
       if( query("max_neili", me)<1500 )
               return notify_fail("你的內力修為不足，沒有辦法練大乘佛索。\n");
               
       if ((int)me->query_skill("shaolin-xinfa", 1) < 120)
               return notify_fail("你的少林心法火候太淺。\n");
               
       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "whip" )
               return notify_fail("你必須先找一條鞭子才能練鞭法。\n");
       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;
        level   = (int) me->query_skill("dacheng-fosuo",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if( query("jingli", me)<100 )
                return notify_fail("你的體力不夠練大乘佛索。\n");
       if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練大乘佛索。\n");
       addn("jingli", -20, me);
       addn("neili", -40, me);
       return 1;
}

string perform_action_file(string action)
{
               return __DIR__"dacheng-fosuo/" + action;
}
