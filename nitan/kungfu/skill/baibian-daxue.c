// baibian-daxue.c
inherit SKILL;

mapping *action = ({
([      "action":"$N一招「指點江山」，手中$w疾點向$n的期門穴!",
        "force" : 60,
        "dodge" : 20,
        "damage" : 22,
        "lvl" : 0,
        "damage_type" : "刺傷",
        "skill_name" : "指點江山",
]),
([      "action":"$N吐氣開聲一招「銀鈎鐵劃」，$w如靈蛇吞吐，向$n白海穴戳去",
        "force" : 90,
        "dodge" : 15,
        "damage" : 28,
        "lvl" : 9,
        "damage_type": "刺傷",
        "skill_name" : "銀鈎鐵劃",
]),
([      "action":"$N向前跨上一步，手中$w一晃，正是一招使出「靈蛇吐霧」，疾點$n的地倉穴",
        "force" : 120,
        "dodge" : 10,
        "damage" : 32,
        "lvl" : 19,
        "damage_type" : "刺傷",
        "skill_name" : "靈蛇吐霧",
]),
([      "action":"$N手中的$w左右急晃，舞成一段光芒，使出「千變萬化」帶着呼呼風聲籠罩了$n的章門穴",
        "force" : 140,
        "dodge" : 8,
        "damage" : 38,
        "lvl" : 29,
        "damage_type": "刺傷",
        "skill_name" : "千變萬化",
]),
([      "action":"$N飛身躍起，一式「千蛇出洞」，捲起漫天筆影，緊緊裹住$n",
        "force" : 160,
        "dodge" : 15,
        "damage" : 44,
        "lvl" : 39,
        "damage_type": "刺傷",
        "skill_name" : "千蛇出洞",
]),
([      "action":"$N凝氣守中，$w逼出陣陣光芒，揮出「靈台觀景」，一招快一招地攻向$n",
        "force" : 190,
        "dodge" : 12,
        "damage" : 49,
        "lvl" : 59,
        "damage_type": "刺傷",
        "skill_name" : "靈台觀景",
]),
([      "action":"$N使出一招「神蛇引路」挺筆中宮直進，$w忽的顫動，中途忽然轉而向上變幻無方",
        "force" : 230,
        "dodge" : 5,
        "damage" : 53,
        "lvl" : 79,
        "damage_type": "刺傷",
        "skill_name" : "神蛇引路",
]),
([      "action":"$N側身手中的$w斜刺，一招「奇採迭出」，刺向$n胸前檀中大穴",
        "force" : 250,
        "dodge" : 15,
        "damage" : 58,
        "lvl" : 99,
        "damage_type": "刺傷",
        "skill_name" : "奇採迭出",
]),
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠，沒有辦法練百變打穴法。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，還不能學習百變打穴法!\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("baibian-daxue", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的百變打穴杖法。\n");

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
       level   = (int) me->query_skill("baibian-daxue",1);
       for(i = sizeof(action); i > 0; i--)
               if(level > action[i-1]["lvl"])
                       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object ob;
        if( !(ob=query_temp("weapon", me)) || 
            query("skill_type", ob) != "staff" )
                return notify_fail("你必須先找一根鐵杖才能學習百變打穴法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的氣不夠，沒有辦法練習百變打穴法。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠，沒有辦法練習百變打穴法。\n");

        me->receive_damage("qi", 32);
        addn("neili", -15, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__ "baibian-daxue/" + action;
}
