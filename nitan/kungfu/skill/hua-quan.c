inherit SKILL;

mapping *action = ({
([      "action": "只見$N身形一矮，大喝聲中一個「斜身攔門插鐵閂」對準$n呼地砸去",
        "force" : 60,
        "attack": 20,
        "dodge" : 40,
        "parry" : 5,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "斜身攔門插鐵閂",
        "damage_type":  "砸傷"
]),
([      "action": "$N左手一分，右拳運氣，一招「曉星當頭即走拳」便往$n的$l招呼過去",
        "force" : 80,
        "attack": 25,
        "dodge" : 43,
        "parry" : 6,
        "damage": 7,
        "lvl"   : 30,
        "skill_name" : "曉星當頭即走拳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N右拳在$n面門一晃，左掌使了個「出勢跨虎西嶽傳」往$n狠命一拳",
        "force" : 100,
        "attack": 28,
        "dodge" : 45,
        "parry" : 8,
        "damage": 10,
        "lvl"   : 60,
        "skill_name" : "出勢跨虎西嶽傳",
        "damage_type":  "抓傷"
]),
([      "action": "$N左拳拉開，右拳帶風，一招「金鵬展翅庭中站」勢不可擋地擊向$n",
        "force" : 120,
        "attack": 35,
        "dodge" : 47,
        "parry" : 11,
        "damage": 17,
        "lvl"   : 80,
        "skill_name" : "金鵬展翅庭中站",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N拉開架式，一招「韋陀獻抱在胸前」使出，底下卻飛踢$n的$l",
        "force" : 140,
        "attack": 40,
        "dodge" : 49,
        "parry" : 13,
        "damage": 20,
        "lvl"   : 100,
        "skill_name" : "韋陀獻抱在胸前",
        "damage_type":  "瘀傷"
]),
([      "action": "$N左手往$n身後一抄，一招「把臂攔門橫鐵閂」便往$n面門砸去",
        "force" : 160,
        "attack": 45,
        "dodge" : 52,
        "parry" : 16,
        "damage": 22,
        "lvl"   : 120,
        "skill_name" : "把臂攔門橫鐵閂",
        "damage_type":  "砸傷"
]),
([      "action": "$N拉開後弓步，雙掌使了個「魁鬼仰鬥撩綠欄」往$n的$l狠力一推",
        "force" : 200,
        "attack": 48,
        "dodge" : 54,
        "parry" : 18,
        "damage": 28,
        "lvl"   : 140,
        "skill_name" : "魁鬼仰鬥撩綠欄",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N運足氣力使出「出勢跨虎西嶽傳」，連攻數拳，全部擊向$n的$l",
        "force" : 220,
        "attack": 51,
        "dodge" : 57,
        "parry" : 20,
        "damage": 32,
        "lvl"   : 160,
        "skill_name" : "出勢跨虎西嶽傳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N往後一縱，就勢使了個「白猿偷桃拜天庭」，右腿掃向$n的$l",
        "force" : 260,
        "attack": 55,
        "dodge" : 61,
        "parry" : 21,
        "damage": 35,
        "lvl"   : 180,
        "skill_name" : "白猿偷桃拜天庭",
        "damage_type":  "砸傷"
]),
([      "action": "$N一個轉身，左掌護胸，右掌反手使了個「吳王試劍劈玉磚」往$n當頭劈落",
        "force" : 280,
        "attack": 60,
        "dodge" : 63,
        "parry" : 23,
        "damage": 37,
        "lvl"   : 200,
        "skill_name" : "吳王試劍劈玉磚",
        "damage_type":  "砸傷"
]),
([      "action": "$N飛身躍起，一招「撤身倒步一溜煙」，腳踢$n面門，隨即雙拳已到$n$l",
        "force" : 300,
        "attack": 62,
        "dodge" : 65,
        "parry" : 25,
        "damage": 40,
        "lvl"   : 220,
        "skill_name" : "撤身倒步一溜煙",
        "damage_type":  "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練西嶽華拳必須空手。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，無法練習西嶽華拳。\n");

        if ((int)me->query_skill("cuff", 1) < 40)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("hua-quan", 1))
                return notify_fail("你的基本拳法火候有限，無法領會更高深的西嶽華拳。\n");

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
        level = (int)me->query_skill("hua-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練習西嶽華拳。\n");

        me->receive_damage("qi", 65);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hua-quan/" + action;
}