inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「雁行斜擊」，身形斜飛，手中$w輕輕點向$n的$l",
        "force"  : 2,
        "dodge"  : 20,
        "parry"  : 10,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N長躍而起，「白虹經天」，$w猛然下刺",
        "force"  : 4,
        "dodge"  : 15,
        "parry"  : 10,
        "damage" : 4,
        "lvl"    : 4,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「浪跡天涯」，揮劍直劈，威不可當",
        "force"  : 5,
        "attack" : 1,
        "dodge"  : 15,
        "parry"  : 10,
        "damage" : 5,
        "lvl"    : 9,
        "damage_type" : "內傷"
]),
([      "action" : "$N使「花前月下」一招自上而下搏擊，模擬冰輪橫空、清光鋪地的光景",
        "force"  : 6,
        "attack" : 2,
        "dodge"  : 15,
        "parry"  : 10,
        "damage" : 6,
        "lvl"    : 14,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w顫動，如鮮花招展來回揮削，只幌得$n眼花撩亂，渾不知從何攻來",
        "force"  : 8,
        "attack" : 4,
        "dodge"  : 15,
        "parry"  : 15,
        "damage" : 7,
        "lvl"    : 19,
        "damage_type" : "內傷"
]),
([      "action" : "$N使出「清飲小酌」劍柄提起，劍尖下指，有如提壺斟酒，直揮$n的$l",
        "force"  : 10,
        "attack" : 6,
        "dodge"  : 15,
        "parry"  : 15,
        "damage" : 8,
        "lvl"    : 24,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w由內自外一刺，左手如斟茶壺，使出「掃雪烹茶」來",
        "force"  : 20,
        "attack" : 8,
        "dodge"  : 10,
        "parry"  : 15,
        "damage" : 9,
        "lvl"    : 29,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左掌橫擺胸前，右手中$w輕輕揮拂，卻是一招「撫琴按蕭」",
        "force"  : 30,
        "attack" : 10,
        "dodge"  : 15,
        "parry"  : 15,
        "damage" : 10,
        "lvl"    : 34,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「松下對弈」，$w自右向左揮一個大弧，刺向$n的$l",
        "force"  : 40,
        "attack" : 11,
        "dodge"  : 15,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 39,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左手如拂五絃，竟以掌為劍攻向$n，卻是一招「池邊調鶴」",
        "force"  : 50,
        "attack" : 14,
        "dodge"  : 10,
        "parry"  : 20,
        "damage" : 13,
        "lvl" : 44,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「柳絮風飄」，$w輕靈地劃出幾個圓弧，向$n的$l揮去",
        "force"  : 60,
        "attack" : 15,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 15,
        "lvl"    : 49,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「小園藝菊」，手中$w迅疾向$n的下盤連點三點",
        "attack" : 21,
        "force"  : 70,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 19,
        "lvl"    : 54,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「西窗夜話」，手中$w中宮直入，攻向$n的$l",
        "force"  : 80,
        "attack" : 22,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 19,
        "lvl"    : 59,
        "damage_type" : "刺傷"
]),
([      "action" : "$N腳下左高右低，一招「柳蔭聯句」，$w在空中化成一道光環，急攻$n",
        "force"  : 90,
        "attack" : 26,
        "dodge"  : 5,
        "parry"  : 20,
        "damage" : 21,
        "lvl"    : 64,
        "damage_type" : "內傷"
]),
([      "action" : "$N手中$w由下而上捲起，猶如打起竹簾一般，卻是「竹簾臨池」",
        "force"  : 100,
        "attack" : 30,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 25,
        "lvl"    : 70,
        "damage_type" : "刺傷"
]),
([      "action" : "$N做搭弓射箭狀，一招「木蘭射雁」，右手$w直刺$n的$l",
        "force"  : 110,
        "attack" : 31,
        "dodge"  : 20,
        "parry"  : 20,
        "damage" : 21,
        "lvl"    : 76,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左手劍訣一領，右手$w平平刺向$n的$l，是一招「雙蝶迷回」",
        "force"  : 120,
        "attack" : 33,
        "dodge"  : 40,
        "parry"  : 20,
        "damage" : 25,
        "lvl"    : 82,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w合身疾刺，一招「孤雲出釉」，直指$n的$l",
        "force"  : 130,
        "attack" : 36,
        "dodge"  : 30,
        "parry"  : 20,
        "damage" : 22,
        "lvl"    : 88,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「幽蘭空谷」，$w看似隨意地一揮，從$n不可思議的角度攻入",
        "force"  : 140,
        "attack" : 37,
        "dodge"  : 20,
        "parry"  : 25,
        "damage" : 25,
        "lvl"    : 94,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「茶花滿路」，一時間空中盡是$w的影子，令$n不知如何抵擋",
        "force"  : 150,
        "attack" : 40,
        "dodge"  : 45,
        "parry"  : 25,
        "damage" : 23,
        "lvl"    : 100,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「陌路採桑」，$w連點數點，疾刺$n的$l",
        "force"  : 160,
        "attack" : 43,
        "dodge"  : 35,
        "parry"  : 25,
        "damage" : 27,
        "lvl"    : 99,
        "damage_type" : "刺傷"
]),
([      "action" : "$N突然盤蹲下來，一招「秋雨蕭蕭」，$w自下而上刺向$n",
        "force"  : 170,
        "attack" : 46,
        "dodge"  : 25,
        "parry"  : 25,
        "damage" : 29,
        "lvl"    : 106,
        "damage_type" : "刺傷"
]),
([      "action" : "$N錯開腳步，手中$w突然從自己的肋下刺出，卻是一招「琴心劍膽」",
        "force"  : 180,
        "attack" : 48,
        "dodge"  : 35,
        "parry"  : 25,
        "damage" : 31,
        "lvl"    : 112,
        "damage_type" : "刺傷"
]),
([      "action" : "$N猶如在水面滑行一般，一招「池塘秋夜」，平平地向$n的$l揮去",
        "force"  : 210,
        "attack" : 51,
        "dodge"  : 40,
        "parry"  : 25,
        "damage" : 35,
        "lvl"    : 118,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「皓腕玉鐲」，手中$w刺點$n的手腕",
        "force"  : 245,
        "attack" : 53,
        "dodge"  : 45,
        "parry"  : 54,
        "damage" : 80,
        "lvl"    : 124,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「牡丹含淚」，$w繞出數個銀圈，平平地向$n的$l捲去",
        "force"  : 270,
        "attack" : 57,
        "dodge"  : 45,
        "parry"  : 62,
        "damage" : 94,
        "lvl"    : 131,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左腳輕點地面，身形往前一撲，一招「芍藥藴珠」，$w向$n的$l刺去",
        "force"  : 290,
        "attack" : 52,
        "dodge"  : 45,
        "parry"  : 70,
        "damage" : 103,
        "lvl"    : 148,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「檐前飛燕」，身形躍起，手中$w掃向$n的$l",
        "force"  : 320,
        "attack" : 66,
        "dodge"  : 50,
        "parry"  : 78,
        "damage" : 115,
        "lvl"    : 164,
        "damage_type" : "刺傷"
]),

([      "action" : "$N臉現黯然之色，隨意一招「蒹葭蒼蒼」，$w刺向$n的$l",
        "force"  : 340,
        "attack" : 82,
        "dodge"  : 65,
        "parry"  : 90,
        "damage" : 130,
        "lvl"    : 178,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry"; 
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不到，無法學習玉女素心劍。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法水平太低，無法學習玉女素心劍。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，不能學習玉女素心劍。\n");

        if (me->query_skill("sword", 1) < me->query_skill("suxin-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的玉女素心劍。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;  
        level = (int) me->query_skill("suxin-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<75 )
                return notify_fail("你的體力不夠練玉女素心劍。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不足以練玉女素心劍。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"suxin-jian/" + action;
}