// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w冒出陣陣寒氣，“唰”地一聲出奇不意地朝$n的$l刺來",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 25,
        "lvl"    : 0,
        "skill_name" : "飛燕入林",
        "damage_type": "刺傷"
]),
([      "action" : "$N身形下沉，身子不住旋轉，手中$w挽做一團劍花朝$n的$l處削去",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 20,
        "lvl"    : 10,
        "skill_name" : "青龍吐水",
        "damage_type": "刺傷"
]),
([      "action" : "$N手中的$w略走偏鋒，左轉有彎，陰詭無比一招刺向$n的$l",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 25,
        "lvl"    : 20,
        "skill_name" : "鳳凰摯窩",
        "damage_type": "刺傷"
]),
([      "action" : "$N手中$w一揮，劍式大開大闔，只見瞬時萬般劍影朝$n的$l處刺來",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 35,
        "lvl"    : 30,
        "skill_name" : "玉女脱衣",
        "damage_type": "刺傷"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("moshen-jianfa", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的魔神劍法。\n");

        return 1;
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
        level = (int) me->query_skill("moshen-jianfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練魔神劍法。\n");

        if( query("neili", me)<10 )
                return notify_fail("你的內力不夠練魔神劍法。\n");

        me->receive_damage("qi", 25);
        addn("neili", -10, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-jianfa/" + action;
}