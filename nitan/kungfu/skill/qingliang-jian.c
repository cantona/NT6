// qingliang-jian.c  清涼劍法

inherit SHAOLIN_SKILL;
mapping *action = ({
([      "action" : "$N舉劍過頂，彎腰躬身，恭敬一式「清風送暖」，$w向$n的$l輕輕刺去，",
        "force" : 120,
        "dodge" : 20,
        "damage" : 35,
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "突然間劍光一吐，長劍化作一道白虹，$N使出一式「風清似水」，劍氣古樸，$w直刺$n的$l",
        "force" : 140,
        "dodge" : 15,
        "damage" : 50,
        "lvl" : 10,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左手向外一分，右手$w向右掠出一招「風聲四起」，劍氣森然地向$n的$l揮去",
        "force" : 200,
        "dodge" : 15,
        "damage" : 60,
        "lvl" : 20,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一劍從空中疾劈而下，招式看似平平無奇，但呼的一聲響，實有石破天驚的氣勢，一招「涼風決」$w如虹地刺向$n的$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 70,
        "lvl" : 30,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一柄$w自半空中橫過，劍身似曲似直，如一件活物一般，一式「清水涼風」奔騰矯夭，氣勢雄渾地斬向$n的$l",
        "force" : 270,
        "dodge" : 10,
        "damage" : 80,
        "lvl" : 40,
        "damage_type" : "割傷"
]),
([      "action" : "$N威儀整肅一式「玉井天池」，$w轟然一動，猶如千軍萬馬奔馳而來，疾疾刺向$n的$l",
        "force" : 280,
        "dodge" : 5,
        "damage" : 90,
        "lvl" : 50,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍轉一式「疊翠浮青」，儼然長槍大戟，黃沙千裡，$w電閃雷鳴，將$n籠罩于重重劍氣之中",
        "force" : 300,
        "dodge" : 5,
        "damage" : 110,
        "lvl" : 60,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍尖向下，一招「清風影動」，$w忽然急轉直上，劍氣將$n的上身要害團團圍住",
        "force" : 380,
        "dodge" : -5,
        "damage" : 135,
        "lvl" : 70,
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
              if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        if ( (int)me->query_skill("shaolin-xinfa", 1) < 50)
                return notify_fail("你的少林心法火候太淺。\n");
        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的基本劍法火候尚淺。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("qingliang-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練清涼劍法。\n");
        me->receive_damage("qi", 35);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingliang-jian/" + action;
}
