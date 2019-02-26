inherit SKILL;

mapping *action = ({
([      "action" : "$N身形急晃，一躍而至$n跟前，右掌帶着切骨寒氣砍向$n的$l",
        "force" : 160,
        "attack": 25,
        "dodge" : -15,
        "parry" : -15,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "切骨寒氣",
        "damage_type" : "割傷"
]),
([      "action" : "$N飛身躍起，雙掌至上而下斜砍而出，頓時萬千道陰風寒勁從四面八方席捲$n",
        "force" : 220,
        "attack": 40,
        "dodge" : -20,
        "parry" : -15,
        "damage": 20,
        "lvl"   : 30,
        "skill_name" : "陰風寒勁",
        "damage_type" : "割傷"
]),
([      "action" : "$N平掌為刀，斜斜砍出，掌勁幻出一片片切骨寒氣如颶風般裹向$n的全身",
        "force" : 280,
        "attack": 50,
        "dodge" : -20,
        "parry" : -25,
        "damage": 28,
        "lvl"   : 60,
        "skill_name" : "切骨寒氣",
        "damage_type" : "割傷"
]),
([      "action" : "$N反轉右掌對準自己護住全身，突然一個筋斗翻至$n面前，左掌橫向$n攔腰砍去",
        "force" : 360,
        "attack": 60,
        "dodge" : -80,
        "parry" : -60,
        "damage": 35,
        "lvl"   : 80,
        "skill_name" : "反轉右掌",
        "damage_type" : "割傷"
]),
([      "action" : "$N右掌後撤，手腕一翻，猛地揮掌砍出，幻出一道寒芒直斬向$n的$l",
        "force" : 420,
        "attack": 110,
        "dodge" : -45,
        "parry" : -40,
        "damage": 50,
        "lvl"   : 100,
        "skill_name" : "寒芒直斬",
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="tougu-zhen"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練陰風刀必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法練習陰風刀。\n");

        if ((int)query("max_neili", me) < 1400)
                return notify_fail("你的內力太弱，無法練習陰風刀。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候不夠，無法練習陰風刀。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yinfeng-dao", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的陰風刀。\n");

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
        level   = (int) me->query_skill("yinfeng-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 100)
                return notify_fail("你的體力太低了。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的內力不夠練陰風刀。\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("yinfeng-dao", 1);
        flvl = query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("yinfeng_dao",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return "$n只感一陣刮骨之痛，看來是受了對方陰風刀內勁的干擾。\n";
        }
}

string perform_action_file(string action)
{
        return __DIR__"yinfeng-dao/" + action;
}