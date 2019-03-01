// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N手中$w冒出陣陣寒氣，“唰”地一聲出奇不意地朝$n的$l劈來",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "停車問路",
        "damage_type" : "割傷"
]),
([      "action": "$N身形下沉，身子不住旋轉，手中$w挽做一團刀花朝$n的$l處削去",
        "force" : 30,
        "dodge" : 30,
        "parry" : 40,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "童子掛畫",
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w一揮，招式大開大闔，只見瞬時萬般刀光朝$n的$l處砍去",
        "force" : 40,
        "dodge" : 35,
        "parry" : 45,
        "damage": 15,
        "lvl"   : 40,
        "skill_name"  : "推窗望月",
        "damage_type" : "割傷"
]),
([      "action": "$N手中的$w略走偏鋒，左轉有彎，陰詭無比一招砍向$n的$l",
        "force" : 60,
        "dodge" : 45,
        "parry" : 45,
        "damage": 20,
        "lvl"   : 60,
        "skill_name"  : "開門見山",
        "damage_type" : "割傷"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("moshen-daofa", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的魔神刀法。\n");

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
        level = (int) me->query_skill("moshen-daofa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練魔神刀法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練魔神刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-daofa/" + action;
}