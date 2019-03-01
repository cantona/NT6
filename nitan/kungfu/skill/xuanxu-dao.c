inherit SKILL;

mapping *action = ({
([      "action": "$N一式「黃雲萬裡動風色，白波九道流雪山」，腳踏「巽」位，手中$w劈出九道光影撲向\n"
                  "$n的$l",
        "force" : 30,
        "attack": 25,
        "dodge" : 20,
        "parry" : 25,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "割傷"
]),
([      "action": "$N一式「銀河倒掛三石樑，香爐瀑布遙相望」，搶佔「坎」位，手中$w化做片片刀光, 似\n"
                  "銀河倒瀉般揮向$n$l",
        "force" : 33,
        "attack": 32,
        "dodge" : 26,
        "parry" : 38,
        "damage": 18,
        "lvl"   : 20,
        "damage_type" : "割傷"
]),
([      "action": "$N一式「登高壯觀天地間，大江茫茫去不黃」，閃向「震」位，手中$w化為漫天刀影，夾\n"
                  "著隱隱雷聲，攻向$n$l",
        "force" : 40,
        "attack": 38,
        "dodge" : 32,
        "parry" : 43,
        "damage": 22,
        "lvl"   : 40,
        "damage_type" : "割傷"
]),
([      "action": "$N一式「山川蕭條極邊土，胡騎憑陵雜風雨」，神情寂寥寡歡，在「艮」位突發一刀，以力壓\n"
                  "千鈞之勢劈向$n$l",
        "force" : 60,
        "attack": 42,
        "dodge" : 45,
        "parry" : 45,
        "damage": 26,
        "lvl"   : 60,
        "damage_type" : "割傷"
]),
([      "action": "$N一式「輪台九月風夜吼，一川碎石大如鬥」，身體急速旋轉，在「離」位如一團旋風，手中\n"
                  "$w唰地砍向$n的$l",
        "force" : 80,
        "attack": 45,
        "dodge" : 50,
        "parry" : 55,
        "damage": 32,
        "lvl"   : 80,
        "damage_type" : "割傷"
]),
([      "action": "$N一式「殺氣三時作陣雲，寒聲一夜傳刁鬥」，佔住「兌」位，手中$w帶著滿天殺氣劈向\n"
                  "$n的$l",
        "force" : 90,
        "attack": 52,
        "dodge" : 65,
        "parry" : 55,
        "damage": 40,
        "lvl"   : 100,
        "damage_type" : "割傷"
]),
});
int valid_enable(string usage) { return (usage == "blade") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("xuanxu-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的玄虛刀法。\n");

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
        level = (int) me->query_skill("xuanxu-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        ||  query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練玄虛刀法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練玄虛刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuanxu-dao/" + action;
}
