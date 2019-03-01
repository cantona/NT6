
// wenjia-daofa.c 溫家刀法（NPC功夫）

inherit SKILL;

mapping *action = ({
([
        "action" : "$N一式「蒼鬆迎客」，身體微側，刀鋒平引，斜劈$n的$l",
        "lvl" : 0,
        "skill_name" : "蒼鬆迎客",
        "damage_type" : "刺傷"
]),
([
        "action" : "$N向前躍上一步，右手急速舞動手中的$w，一招「開門見山」直挑$n的$l",
        "lvl" : 10,
        "skill_name" : "開門見山",
        "damage_type" : "刺傷"
]),
([
        "action" : "$N一個斜側步，一招「聞雞起舞」，手中$w平平的推向$n的$l",
        "lvl" : 20,
        "skill_name" : "聞雞起舞",
        "damage_type" : "刺傷"
]),
([
        "action" : "$N一招「推波助瀾」，手裡的$w劃出一個大弧，急速砍向$n的$l",
        "lvl" : 30,
        "skill_name" : "推波助瀾",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return (usage == "blade") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不對。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的內力不夠。\n");
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
        int i, level, j;
        level   = (int) me->query_skill("wenjia-daofa",1);
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);
                        return ([  
                                "action":       action[j]["action"],
                                "lvl":          action[j]["lvl"],
                                "damage_type":  action[j]["damage_type"],
                                "force":        150+random(300),
                                "dodge":        random(30),
                                "parry":        random(30),
                                "damage":       60 + random(100),
                        ]);
                }
        }
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 40)
                return notify_fail("你的體力不夠練溫家刀法。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的內力不夠練溫家刀法。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"wenjia-daofa/" + action;
}

