// wuzhan-mei.c 五展梅

inherit SKILL;

mapping *action = ({
([      "action" : "$N一招“五展梅”「冬梅初吐蕊」，手中$w猶如點點淡黃色的梅蕊刺向$n的$l",
        "force" : 60,
        "dodge" : 2,
        "parry" : 10,
        "skill_name" : "冬梅初吐蕊",
        "lvl" : 0,
        "damage" : 70,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出“五展梅”「幼梅傲霜雪」，$n只覺劍氣撲面而來，仿佛置身冰天雪地中，\n"
                   "$w仿佛化作傲霜的梅枝刺向$n的$l",
        "force" : 100,
        "dodge" : 0,
        "parry" : 20,
        "skill_name" : "幼梅傲霜雪",
        "lvl" : 20,
        "damage" : 90,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招“五展梅”「勁梅笑迎春」，$w連續劃出幾個圓圈，劍勢如朵朵梅花，\n"
                   "$n眼前一花，$w已攻到面前",
        "force" : 150,
        "dodge" : -2,
        "parry" : 30,
        "skill_name" : "勁梅笑迎春",
        "lvl" : 40,
        "damage" : 110,
        "damage_type" : "刺傷"
]),

([      "action" : "$N一騰身，$w飛舞，正是“五展梅”「臘梅暗香浮」,$n竟似聞到淡淡梅花幽香，\n"
                   "恍惚間心馳神動,劍氣已直刺$n的$l",
        "force" : 200,
        "dodge" : -4,
        "parry" : 50,
        "skill_name" : "臘梅暗香浮",
        "lvl" : 60,
        "damage" : 130,
        "damage_type" : "刺傷"
]),

([      "action" : "$N向前跨上一步，手中$w使出“五展梅”「紅梅展新枝」,劍光爆漲，\n"
                   "快癒閃電直刺$n的$l",
        "force" : 400,
        "dodge" : -6,
        "parry" : 70,
        "skill_name" : "紅梅展新枝",
        "lvl" : 80,
        "damage" : 150,
        "damage_type" : "刺傷"
]),

([      "action" : "$N手中的$w一晃，使出“五展梅”終極招式「五梅花枝俏」,五式合作一式，\n"
                   "瞬間劍意漫天，$n只見梅花四處飛舞，隱藏其中的殺氣已透骨而入",
        "force" : 600,
        "dodge" : -8,
        "parry" : 90,
        "skill_name" : "五梅花枝俏",
        "lvl" : 100,
        "damage" : 170,
        "damage_type" : "刺傷"
]),
});



int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 60)
                return notify_fail("你的碧雲心法太淺。\n");
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
        level   = (int) me->query_skill("wuzhan-mei",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 5, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練五展梅。\n");
        me->receive_damage("qi", 20);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuzhan-mei/" + action;
}
