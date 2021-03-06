inherit SKILL;

mapping *action = ({
([      "action": "在呼呼風聲中，$N使一招「蒼鷹襲兔」，雙手如鈎如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形一躍，費神撲上，使出一招「雄鷹展翅」，右手直直抓向$n的$l",
        "force" : 80,
        "dodge" : 20,
        "parry" : 5,
        "damage": 3,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平伸，十指微微上下抖動，一招「拔翅橫飛」打向$n的$l",    
        "force" : 120,
        "dodge" : 32,
        "parry" : 10,
        "damage": 5,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出一招「迎風振翼」，悄無聲息的遊走至$n身前，猛的一爪奮力抓向$n的$l",
        "force" : 132,
        "dodge" : 38,
        "parry" : 19,
        "damage": 5,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平提胸前，左手護住面門，一招「撥雲瞻日」右手推向$n的$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 7,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出「搏擊長空」，低喝一聲，雙手化掌為爪，一前一後抓向$n的$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 9,
        "damage_type" : "抓傷"
]),
([      "action": "$N使出「鷹揚萬里」，雙爪如狂風驟雨般對準$n的$l連續抓出",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 15,
        "damage_type" : "抓傷"
])
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鷹爪手必須空手。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yingzhao-shou", 1))
                return notify_fail("你的基本爪法火候不足，無法領會更高深的鷹爪手。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "claw" || usage=="parry";
}

string query_skill_name(int lvl)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yingzhao-shou/" + action;
}