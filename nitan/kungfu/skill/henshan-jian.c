#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N右手$w慢慢指出，突然間在空中一顫，嗡嗡作響，劍光暴長，向$n刺去",
        "force"  :  110,
        "dodge"  :  28,
        "damage" :  30,
        "lvl"    :  0,
        "damage_type":  "刺傷"
]),
([      "action" :  "$N手中$w如鬼如魅，竟已繞到$n背後，$n急忙轉身，耳邊只聽得嗡嗡兩聲",
        "force"  :  120,
        "dodge"  :  24,
        "damage" :  25,
        "lvl"    :  20,
        "damage_type":  "刺傷"
]),
([     
        "action" :  "$N手中$w寒光陡閃，手中的$w，猛地反刺，直指$n胸口。這一下出招快\n"
                    "極，抑且如夢如幻，正是「百變千幻衡山雲霧十三式」中的絕招",
        "force"  :  120,
        "dodge"  :  24,
        "damage" :  28,
        "lvl"    :  35,
        "damage_type":  "刺傷",
        "skill_name":   "百變千幻",
]),
([      
        "action" :  "$N不慌不忙猶如蓄勢待發，手中$w刷的一劍「劍發琴音」，向$n$l刺去",
        "force"  :  130, 
        "dodge"  :  30,
        "damage" :  35,
        "lvl"    :  50,
        "damage_type":  "刺傷",
        "skill_name":   "劍發琴音",
]),
([      
        "action" : "$N飛身躍起，一式「歲歲青蒼」，$w發出一聲長嘯從半空中灑向$n的$l",
        "force"  :  160,
        "dodge"  :  38,
        "damage" :  45,
        "lvl"    :  75,
        "damage_type":  "刺傷",
        "skill_name":   "歲歲青蒼",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

            if( query("max_neili", me)<80 )
                return notify_fail("你目前的內力修為不夠，沒有辦法練衡山劍法。\n");

            if (me->query_skill("sword", 1) < 10)
                return notify_fail("你的基本劍法火候太淺，沒有辦法練衡山劍法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("henshan-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的衡山劍法。\n");

            return 1;
}

int valid_enable(string usage)
{
            return usage == "sword" || usage == "parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}


mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("henshan-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
            object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<40 )
                       return notify_fail("你的內力不足，沒有辦法練習衡山劍法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練衡山劍法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"henshan-jian/" + action;
}
