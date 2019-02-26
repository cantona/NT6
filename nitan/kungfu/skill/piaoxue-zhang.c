#include <ansi.h>
inherit SKILL;

mapping *action = ({
([        "action" : "$N劃身錯步，一式「追風逐電」，雙掌內攏外託，同時攻向$n的左肩",
        "force"  : 170,
        "attack" : 85,
        "dodge"  :-38,
        "parry"  :-38,
        "damage" : 36,
        "lvl"    : 0,
        "skill_name" : "追風逐電",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「雲飄四海」，雙掌虛虛實實，以迅雷不及掩耳之勢劈向$n",
        "force"  : 210,
        "attack" : 98,
        "dodge"  :-43,
        "parry"  :-43,
        "damage" : 44,
        "lvl"    : 40,
        "skill_name" : "雲飄四海",
        "damage_type" : "內傷"
]),
([        "action" : "$N使一式「八方雲湧」，勁氣瀰漫，雙掌如輪，一環環向$n的後背斫去",
        "force"  : 280,
        "attack" : 103,
        "dodge"  :-51,
        "parry"  :-51,
        "damage" : 58,
        "lvl"    : 80,
        "skill_name" : "八方雲湧",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「龍捲暴伸」，雙掌似讓非讓，似頂非頂，氣浪如急流般使$n陷身其中",
        "force"  : 340,
        "attack" : 125,
        "dodge"  :-65,
        "parry"  :-65,
        "damage" : 67,
        "lvl"    : 120,
        "skill_name" : "龍捲暴伸",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「冰封萬里」，掌影層層疊疊，飄飄渺渺，凌厲的掌風直湧$n而去",
        "force"  : 370,
        "attack" : 131,
        "dodge"  :-68,
        "parry"  :-68,
        "damage" : 71,
        "lvl"    : 160,
        "skill_name" : "冰封萬里",
        "damage_type" : "內傷"
]),
([        "action" : "$N雙手變幻，五指輕彈，一招「穹寰飛仙」，力分五路，招劃十方籠罩$n",
        "force"  : 410,
        "attack" : 145,
        "dodge"  :-73,
        "parry"  :-73,
        "damage" : 82,
        "lvl"    : 200,
        "skill_name" : "穹寰飛仙",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練飄雪穿雲掌必須空手。\n");

        if( query("con", me)<28 )
                return notify_fail("你的先天根骨欠佳，不能練飄雪穿雲掌。\n");

        if( query("str", me)<32 )
                return notify_fail("你的先天臂力孱弱，不能練飄雪穿雲掌。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，不能練飄雪穿雲掌。\n");

        if (me->query_skill("strike", 1) < 100)
                return notify_fail("你的掌法根基不夠，不能練飄雪穿雲掌。\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("你的內力修為太淺，無法練飄雪穿雲掌。\n");

        if (me->query_skill("strike", 1) < me->query_skill("piaoxue-zhang", 1))
                return notify_fail("你的基本掌法太差，無法領會更高深的飄雪穿雲掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int)me->query_skill("piaoxue-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠練習飄雪穿雲掌。\n");

        if (me->query_skill("sixiang-zhang", 1) < 100)
        {
                me->receive_damage("qi", 60);
                addn("neili", -80, me);
        } else
        {
                me->receive_damage("qi", 80);
                addn("neili", -100, me);
        }
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("piaoxue-zhang", 1);

        if (damage_bonus < 180 || lvl < 160) return 0;

        if (damage_bonus / 2 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 140) / 2, me);
                        return HIR "只聽$n" HIR "前胸“喀嚓”一聲悶響，竟"
                               "似折斷了一跟肋骨。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"piaoxue-zhang/"+ action;
}