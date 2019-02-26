inherit SKILL;

mapping *action = ({
([      "action": "只見$N身形一矮，大喝聲中一個「沖天炮」對準$n的鼻子呼地砸去",
        "force" : 60,
        "attack": 20,
        "dodge" : 40,
        "parry" : 5,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "沖天炮",
        "damage_type":  "砸傷"
]),
([      "action": "$N左手一分，右拳運氣，一招「拔草尋蛇」便往$n的$l招呼過去",
        "force" : 80,
        "attack": 25,
        "dodge" : 43,
        "parry" : 6,
        "damage": 7,
        "lvl"   : 30,
        "skill_name" : "拔草尋蛇",
        "damage_type":  "瘀傷"
]),
([      "action": "$N右拳在$n面門一晃，左掌使了個「葉底偷桃」往$n的$l狠命一抓",
        "force" : 100,
        "attack": 28,
        "dodge" : 45,
        "parry" : 8,
        "damage": 10,
        "lvl"   : 60,
        "skill_name" : "葉底偷桃",
        "damage_type":  "抓傷"
]),
([      "action": "$N左拳拉開，右拳帶風，一招「黑虎掏心」勢不可擋地擊向$n$l",
        "force" : 120,
        "attack": 35,
        "dodge" : 47,
        "parry" : 11,
        "damage": 17,
        "lvl"   : 80,
        "skill_name" : "黑虎掏心",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N拉開架式，一招「雙風貫耳」使出，底下卻飛起一腳踢向$n$l",
        "force" : 140,
        "attack": 40,
        "dodge" : 49,
        "parry" : 13,
        "damage": 20,
        "lvl"   : 100,
        "skill_name" : "雙風貫耳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N大喝一聲，左手往$n身後一抄，右拳便往$n面門砸了過去",
        "force" : 160,
        "attack": 45,
        "dodge" : 52,
        "parry" : 16,
        "damage": 22,
        "lvl"   : 120,
        "skill_name" : "龍虎相交",
        "damage_type":  "砸傷"
]),
([      "action": "$N拉開後弓步，雙掌使了個「如封似閉」往$n的$l一推",
        "force" : 200,
        "attack": 48,
        "dodge" : 54,
        "parry" : 18,
        "damage": 28,
        "lvl"   : 140,
        "skill_name" : "如封似閉",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N運足氣力，一連三拳擊向$n$l，力道一拳高過一拳",
        "force" : 220,
        "attack": 51,
        "dodge" : 57,
        "parry" : 20,
        "damage": 32,
        "lvl"   : 160,
        "skill_name" : "陽關三疊",
        "damage_type":  "瘀傷"
]),
([      "action": "$N往後一縱，就勢使了個「老樹盤根」，右腿掃向$n的$l",
        "force" : 260,
        "attack": 55,
        "dodge" : 61,
        "parry" : 21,
        "damage": 35,
        "lvl"   : 180,
        "skill_name" : "老樹盤根",
        "damage_type":  "砸傷"
]),
([      "action": "$N一個轉身，左掌護胸，右掌反手使了個「獨劈華山」往$n當頭一劈",
        "force" : 280,
        "attack": 60,
        "dodge" : 63,
        "parry" : 23,
        "damage": 37,
        "lvl"   : 200,
        "skill_name" : "獨劈華山",
        "damage_type":  "砸傷"
]),
([      "action": "$N飛身躍起，一招「蒼鷹捕鼠」，腳踢$n面門，隨即雙拳已到$n的$l",
        "force" : 300,
        "attack": 62,
        "dodge" : 65,
        "parry" : 25,
        "damage": 40,
        "lvl"   : 220,
        "skill_name" : "",
        "damage_type":  "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo) { return combo == "chuncan-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練胡家拳必須空手。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠，無法練習胡家拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("hujia-quan", 1))
                return notify_fail("你的基本拳法火候有限，無法領會更高深的胡家拳法。\n");

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
        level = (int)me->query_skill("hujia-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 65);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hujia-quan/" + action;
}