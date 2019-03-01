// jiuqu-zhegufa.c 九曲折骨法
// Edit By Vin On 22/2/2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N一聲冷哼，以掌化爪，五指如鉤，直逼$n的膻中要穴",
        "force" : 130,
        "attack": 65,
        "dodge" : 5,
        "damage": 85,
        "parry" : 40,
        "lvl"   : 0,
        "damage_type" : "瘀傷"
]),
([      "action": "$N左手虛晃，右手上下直擊，反扣$n的肩井大穴",
        "force" : 160,
        "attack": 72,
        "dodge" : 10,
        "damage": 92,
        "parry" : 42,
        "lvl"   : 30,
        "damage_type" : "瘀傷"
]),
([      "action": "$N一矮身，掌指齊出，拍拿並施，拿向$n的三路要害",
        "force" : 180,
        "attack": 81,
        "dodge" : 15,
        "parry" : 45,
        "damage": 130,
        "lvl"   : 60,
        "damage_type" : "瘀傷"
]),
([      "action": "$N左手鷹抓，右手蛇舉，身形微微晃動，雙手疾扣$n的中節大脈",
        "force" : 230,
        "attack": 85,
        "dodge" : 20,
        "parry" : 46,
        "damage": 140,
        "lvl"   : 90,
        "damage_type" : "瘀傷"
]),
([      "action": "$N上前一步，四面八方出現無數掌影，一爪突出，抓向$n的胸口",
        "force" : 240,
        "attack": 93,
        "dodge" : 25,
        "parry" : 54,
        "damage": 150,
        "lvl" : 120,
        "damage_type" : "內傷"
]),
([      "action": "$N大喝一聲，兩手環扣，全身關節啪啪作響，擊向$n的$l",
        "force" : 270,
        "attack": 98,
        "dodge" : 30,
        "parry" : 58,
        "damage": 160,
        "lvl" : 150,
        "damage_type" : "內傷"
]),
([      "action": "$N身形一展，十指齊伸，遮天蔽日般地籠罩$n的全身要穴",
        "force" : 330,
        "attack": 101,
        "dodge" : 35,
        "parry" : 62,
        "damage": 170,
        "lvl" : 180,
        "damage_type" : "內傷"
]),
([      "action": "$N岳立霆峙，在一陣暴雷聲中，雙手同時拍向$n的全身各處",
        "force" : 380,
        "attack": 127,
        "dodge" : 50,
        "parry" : 65,
        "damage": 180,
        "lvl" : 210,
        "damage_type" : "內傷"
])
});

int valid_enable(string usage)
{
        return usage == "hand" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練九曲折骨法必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法學九曲折骨法。\n");

        if( query("max_neili", me)<2800 )
                return notify_fail("你的內力太弱，無法練九曲折骨法。\n");

        if ((int)me->query_skill("hand", 1) < 180)
                return notify_fail("你的基本手法火候不夠，無法學九曲折骨法。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("jiuqu-zhegufa", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的九曲折骨法。\n");

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
        level = (int) me->query_skill("jiuqu-zhegufa",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("九曲折骨法必須空手練習。\n");

        if( query("qi", me)<120 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠練九曲折骨法。\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string *limbs;
        string  limb;

        if (damage_bonus < 200) return 0;

        if (damage_bonus / 5 > victim->query_dex())
        {
                if( arrayp(limbs=query("limbs", victim)) )
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "罩門";

                victim->receive_wound("qi", (damage_bonus - 200) / 2);
                return HIR "$n" HIR "稍一遲疑，只見$N" HIR "手正搭在自己" + limb +
                       "上，只聽「□嚓」一聲脆響，此處骨骼頓時應聲而碎！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"jiuqu-zhegufa/" + action;
}