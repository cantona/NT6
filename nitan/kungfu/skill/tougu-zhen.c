inherit SKILL;

mapping *action = ({
([      "action" : "$N將內勁貫住指尖，攜帶着絲絲陰風一擊凌空射向$n的$l",
        "force" : 140,
        "attack": 25,
        "dodge" : -15,
        "parry" : -15,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "絲絲陰風",
        "damage_type" : "刺傷"
]),
([      "action" : "$N表情麻木，陡的躍身而起，右手食指帶着極寒之氣直射$n的$l",
        "force" : 180,
        "attack": 40,
        "dodge" : -20,
        "parry" : -15,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "極寒之氣",
        "damage_type" : "刺傷"
]),
([      "action" : "$N怪叫一聲，頓在半空翻個筋斗，將要落下之時，突然對準$n的$l處“颼”的一指射出",
        "force" : 220,
        "attack": 50,
        "dodge" : -20,
        "parry" : -25,
        "damage": 38,
        "lvl"   : 60,
        "skill_name" : "一指射出",
        "damage_type" : "刺傷"
]),
([      "action" : "$N提氣遊走，不露身色繞至$n身後，猛的對準$n$l一指射出，$n剛要回擋，卻發"
                   "\n現此招乃是需招，$N至寒的一指已點向$n的後心",
        "force" : 280,
        "attack": 80,
        "dodge" : -80,
        "parry" : -60,
        "damage": 55,
        "lvl"   : 80,
        "skill_name" : "乃是需招",
        "damage_type" : "刺傷"
]),
([      "action" : "$N向後疾退數尺，猛的又奔至$n跟前，左手食指快若疾電般點向$n的$l",
        "force" : 360,
        "attack": 140,
        "dodge" : -45,
        "parry" : -40,
        "damage": 80,
        "lvl"   : 100,
        "skill_name" : "亡命冰原",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="yinfeng-dao"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練透骨針必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法練習透骨針。\n");

        if ((int)query("max_neili", me) < 1400)
                return notify_fail("你的內力太弱，無法練習透骨針。\n");

        if ((int)me->query_skill("finger", 1) < 100)
                return notify_fail("你的基本指法火候不夠，無法練習透骨針。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("tougu-zhen", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的透骨針。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("tougu-zhen",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 100)
                return notify_fail("你的體力太低了。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的內力不夠練透骨針。\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("tougu-zhen", 1);
        flvl = query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("tougu_zhen",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return "$n只感到從傷口處傳來一陣切骨之痛，看來是受了對方透骨針內勁的干擾。\n";
        }
}

string perform_action_file(string action)
{
        return __DIR__"tougu-zhen/" + action;
}