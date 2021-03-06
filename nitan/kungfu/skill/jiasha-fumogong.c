// modify by Rcwiz 2003 for lx and yh

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N左手虛按，右腿使一招「一步等天」，向$n的$l踢去",
        "attack" : 30,
        "force"  : 70,
        "dodge"  : 42,
        "parry"  : 99,
        "damage" : 22,
        "skill_name" : "一步等天",
        "lvl" : 0,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手虛出，右手使一招「袈裟攔雀」，向$n的$l襲去",
        "attack" : 40,
        "force" : 85,
        "dodge" : 81,
        "parry" : 102,
        "damage" : 42,
        "skill_name" : "袈裟攔雀",
        "lvl" : 30,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使一招「直衝拳」，左手回撤，有拳向$n的$l直擊而去",
        "attack" : 50,
        "force" : 100,
        "dodge" : 88,
        "parry" : 105,
        "damage" : 44,
        "skill_name" : "直衝拳",
        "lvl" : 140,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N忽地分開右手上左手下，一招「雙風貫耳」，向$n的$l和麪門打去",
        "attack" : 30,
        "force" : 125,
        "dodge" : 86,
        "parry" : 119,
        "damage" : 45,
        "skill_name" : "雙風貫耳",
        "lvl" : 160,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手由胸前向下，右臂微曲，使一招「伏魔式」，向$n的$l推去",
        "attack" : 56,
        "force" : 150,
        "dodge" : 94,
        "parry" : 115,
        "damage" : 52,
        "skill_name" : "伏魔式",
        "lvl" : 180,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙手回收，一式「反雲手」，向$n的$l推去",
        "attack" : 54,
        "force" : 185,
        "dodge" : 102,
        "parry" : 122,
        "damage" : 83,
        "skill_name" : "反雲手",
        "lvl" : 200,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身體向後騰出，左手略直，右臂微曲，使一招「鎮魔拳」，向$n的$l和麪門打去",
        "attack" : 70,
        "force" : 215,
        "dodge" : 132,
        "parry" : 121,
        "damage" : 82,
        "skill_name" : "鎮魔拳",
        "lvl" : 220,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙手伸開，招「鎮魂式」，將$n渾身上下都籠罩在重重掌影之中",
        "attack" : 81,
        "force" : 260,
        "dodge" : 154,
        "parry" : 145,
        "damage" : 92,
        "skill_name" : "鎮魂式",
        "lvl" : 230,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙手握拳，左手猛地向前推出，一招「蕩魔式」，直奔$n心窩而去",
        "attack" : 90,
        "force" : 285,
        "dodge" : 166,
        "parry" : 175,
        "damage" : 100,
        "skill_name" : "蕩魔式",
        "lvl" : 240,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N飛身而起，半空中雙拳翻滾而出，一招「降妖伏魔」，一股勁風直逼$n",
        "attack" : 120,
        "force" : 340,
        "dodge" : 178,
        "parry" : 185,
        "damage" : 120,
        "skill_name" : "降妖伏魔",
        "lvl" : 250,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練袈裟伏魔功必須空手。\n");

        if( query("str", me)<25 )
                return notify_fail("你先天臂力不足，無法修煉袈裟伏魔功。\n");

        if( query("con", me)<25 )
                return notify_fail("你先天根骨不足，無法修煉袈裟伏魔功。\n");
        
        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的內功火候不夠，無法學袈裟伏魔功。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力太弱，無法練袈裟伏魔功。\n");


        if ((int)me->query_skill("ruying-suixingtui", 1) < 160)
                                return notify_fail("你的如影隨形腿火候不夠，無法學袈裟伏魔功。\n");
        if ((int)me->query_skill("unarmed", 1) < 120)
                return notify_fail("你的基本拳腳火候不夠，無法學袈裟伏魔功。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jiasha-fumogong", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的袈裟伏魔功。\n");

        if ((int)me->query_skill("ruying-suixingtui", 1) < (int)me->query_skill("jiasha-fumogong", 1))
                return notify_fail("你的如影隨形腿水平有限，無法領會更高深的袈裟伏魔功。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiasha-fumogong", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

varargs mixed hit_ob(object me, object victim, int damage_bonus) 
{
        int lvl; 

        lvl = me->query_skill("jiasha-fumogong", 1); 

        if (damage_bonus < 150 
            || lvl < 180 
             || query("neili", me)<300
             || query_temp("weapon", me )
             || query_temp("secondary_weapon", me )
            || me->query_skill_mapped("force") != "yijinjing" 
            || me->query_skill_prepared("unarmed") != "jiasha-fumogong") 
                return 0; 
        {

                addn("neili", -30, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 4, me); 
                return HIY "$N" HIY "內力猛催，突然間一股渾厚無比的的內力" 
                       HIY "透體而入，只聽$n一聲悶哼！\n" NOR; 
        }
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練袈裟伏魔功。\n");

        me->receive_damage("qi", 65);
        addn("neili", -59, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiasha-fumogong/" + action;
}
