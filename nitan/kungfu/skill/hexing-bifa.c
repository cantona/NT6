inherit SKILL;

mapping *action = ({
([      "action":"$N一招「飛鴻展翅」，手中$w猛然點向$n小腹",
        "force" : 120,
        "attack": 24,
        "dodge" : 10,
        "parry" : 20,
        "damage": 45,
        "lvl"   : 0,
        "skill_name" : "飛鴻展翅",
        "damage_type" : "刺傷"
]),
([      "action":"$N不退反進，一招「蘭花撫穴式」，手中$w點向$n天池穴",
        "force" : 150,
        "attack": 40,
        "dodge" : 14,
        "parry" : 30,
        "damage": 60,
        "lvl"   : 40,
        "skill_name" : "蘭花撫穴式",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中$w猛然旋轉，使出「雲開日出」，疾點$n的天門穴",
        "force" : 180,
        "attack": 60,
        "dodge" : 25,
        "parry" : 32,
        "damage": 75,
        "lvl"   : 60,
        "skill_name" : "雲開日出",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中$w呼呼做響，使出「天旋地轉」，$w直打$n的區門穴",
        "force" : 220,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 70,
        "lvl"   : 80,
        "skill_name" : "天旋地轉",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「漫天金光」，手中$w猶如萬千光點向$n飛擊而去",
        "force" : 260,
        "attack": 70,
        "dodge" : 10,
        "parry" : 45,
        "damage": 80,
        "lvl"   : 100,
        "skill_name" : "漫天金光",
        "damage_type" : "刺傷"
]),
([      "action":"$N招式陡然變慢，一招「金羽飛箭」，手中$w如離弦之箭直襲$w要穴",
        "force" : 300,
        "attack": 100,
        "dodge" : 51,
        "parry" : 50,
        "damage": 110,
        "lvl"   : 120,
        "skill_name" : "金羽飛箭",
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "dagger") || (usage == "parry"); }

int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力修為不夠。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "dagger" )
                return notify_fail("你必須先找一把相應的武器才能學習鶴形筆法。\n");

        if ((int)me->query_skill("dagger", 1) < (int)me->query_skill("hexing-bifa", 1))
                return notify_fail("你的基本短兵水平有限，無法領會更高深的鶴形筆法。\n");

    return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("hexing-bifa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習鶴形筆法。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練鶴形筆法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練鶴形筆法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -52, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hexing-bifa/" + action;
}