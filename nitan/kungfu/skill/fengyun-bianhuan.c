//fengyun-bianhuan.c 風雲變幻
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"只見$N腳步變幻不定，身形一晃再晃，一招「無孔不入」，雙拳徑破$n之防守，痛擊$n$l。",
        "force" :100,
        "attack":12,
        "dodge" :30,
        "damage":12,
        "lvl"   :0,
        "skill_name" :"無孔不入",
        "damage_type":"砸傷"
]),
([      "action":"$N暗運真氣，雙腿便似釘在地上一般，一式「拍案齊掌」，接連五六個直拳一氣打向$n$l。",
        "force" :130,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :40,
        "skill_name" :"拍案齊掌",
        "damage_type":"瘀傷"
]),
([      "action":"$N一個橫躍而出，使出一招「意欲凌風翔」，兩拳向下猛擊$n的頭部。",
        "force" :150,
        "attack":32,
        "dodge" :80,
        "damage":40,
        "lvl"   :70,
        "skill_name" :"意欲凌風翔",
        "damage_type":"瘀傷"
]),
([      "action":"$N雙手平舉胸前，使出一招「雷震軒轅」，向前急速推出，擊向$n的$l。",
        "force" :180,
        "attack":46,
        "dodge" :110,
        "damage":52,
        "lvl"   :100,
        "skill_name" :"雷震軒轅",
        "damage_type":"瘀傷"
]),
([      "action":"$N右手微拳，探步向左，使出一招「推窗望月」，右手後縮，肘部重重地撞向$n$l。",
        "force" :220,
        "attack":65,
        "dodge" :150,
        "damage":68,
        "lvl"   :150,
        "skill_name" :"推窗望月",
        "damage_type":"內傷"
]),
([      "action":"$N使出「太華夜碧」，腳下步伐竄動，兩手在胸前交叉，右拳攻向$n$l。",
        "force" :250,
        "attack":78,
        "dodge" :180,
        "damage":80,
        "lvl"   :180,
        "skill_name" :"太華夜碧",
        "damage_type":"內傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("練風雲變幻必須空手。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的內功心法火候太淺，不能學風雲變幻。\n");

     if ((int)me->query_skill("cuff", 1) < 100)
         return notify_fail("你的基本拳法火候不夠。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的內力太低，無法學風雲變幻。\n");

     if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("fengyun-bianhuan", 1))
         return notify_fail("你的基本拳法水平有限，無法領會更高深的風雲變幻。\n");

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
     level = (int) me->query_skill("fengyun-bianhuan", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("練風雲變幻必須空手。\n");

     if( query("qi", me)<100 )
            return notify_fail("你的體力不夠練風雲變幻。\n");

     if( query("neili", me)<90 )
            return notify_fail("你的內力不夠練風雲變幻。\n");

     me->receive_damage("qi", 85);
     addn("neili", -65, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"fengyun-bianhuan/" + action;
}
