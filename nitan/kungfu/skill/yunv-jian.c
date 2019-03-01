#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N一招"+(order[random(13)])+"「雁行斜擊」"NOR"，身形斜飛，手中$w輕輕點向$n的$l",
        "lvl" : 0,
        "skill_name" : "雁行斜擊"
]),
([        "action" : "$N長躍而起，"+(order[random(13)])+"「白虹經天」"NOR"，$w猛然下刺",
        "lvl" : 4,
        "skill_name" :  "白虹經天"
]),
([        "action" : "$N使出"+(order[random(13)])+"「浪跡天涯」"NOR"，揮劍直劈，威不可當",
        "lvl" : 9,
        "skill_name" :  "浪跡天涯"
]),
([        "action" : "$N使"+(order[random(13)])+"「花前月下」"NOR"一招自上而下搏擊，模擬冰輪橫空、清光舖地的光景",
        "lvl" : 14,
        "skill_name" :  "花前月下"
]),
([        "action" : "$N手中$w顫動，一招"+(order[random(13)])+"「鮮花招展」"NOR"來回揮削，只幌得$n眼花撩亂，渾不知從何攻來",
        "lvl" : 19,
        "skill_name" :  "鮮花招展"
]),
([        "action" : "$N使出"+(order[random(13)])+"「清飲小酌」"NOR"劍柄提起，劍尖下指，有如提壺斟酒，直揮$n的$l",
        "lvl" : 24,
        "skill_name" :  "清飲小酌"
]),
([        "action" : "$N手中$w由內自外一刺，左手如斟茶壺，使出"+(order[random(13)])+"「掃雪烹茶」"NOR"來",
        "lvl" : 29,
        "skill_name" :  "掃雪烹茶"
]),
([        "action" : "$N左掌橫擺胸前，右手中$w輕輕揮拂，卻是一招"+(order[random(13)])+"「撫琴按蕭」"NOR"",
        "lvl" : 34,
        "skill_name" :  "撫琴按蕭"
]),
([        "action" : "$N一招"+(order[random(13)])+"「鬆下對弈」"NOR"，$w自右向左揮一個大弧，刺向$n的$l",
        "lvl" : 39,
        "skill_name" :  "鬆下對弈"
]),
([        "action" : "$N左手如拂五弦，竟以掌為劍攻向$n，卻是一招"+(order[random(13)])+"「池邊調鶴」"NOR"",
        "lvl" : 44,
        "skill_name" :  "池邊調鶴"
]),
([        "action" : "$N一招"+(order[random(13)])+"「柳絮風飄」"NOR"，$w輕靈地劃出幾個圓弧，向$n的$l揮去",
        "lvl" : 49,
        "skill_name" :  "柳絮風飄"
]),
([        "action" : "$N一招"+(order[random(13)])+"「小園藝菊」"NOR"，手中$w迅疾向$n的下盤連點三點",
        "lvl" : 54,
        "skill_name" :  "小園藝菊"
]),
([        "action" : "$N使出"+(order[random(13)])+"「西窗夜話」"NOR"，手中$w中宮直入，攻向$n的$l",
        "lvl" : 59,
        "skill_name" :  "西窗夜話"
]),
([        "action" : "$N腳下左高右低，一招"+(order[random(13)])+"「柳蔭聯句」"NOR"，$w在空中化成一道光環，急攻$n",
        "lvl" : 64,
        "skill_name" :  "柳蔭聯句"
]),
([        "action" : "$N手中$w由下而上卷起，猶如打起竹簾一般，卻是"+(order[random(13)])+"「竹簾臨池」"NOR"",
        "lvl" : 70,
        "skill_name" :  "竹簾臨池"
]),
([        "action" : "$N做搭弓射箭狀，一招"+(order[random(13)])+"「木蘭射雁」"NOR"，右手$w直刺$n的$l",
        "lvl" : 76,
        "skill_name" :  "木蘭射雁"
]),
([        "action" : "$N左手劍訣一領，右手$w平平刺向$n的$l，是一招"+(order[random(13)])+"「雙蝶迷回」"NOR"",
        "lvl" : 82,
        "skill_name" :  "雙蝶迷回"
]),
([        "action" : "$N手中$w合身疾刺，一招"+(order[random(13)])+"「孤雲出釉」"NOR"，直指$n的$l",
        "lvl" : 88,
        "skill_name" : "孤雲出釉"
]),
([        "action" : "$N一招"+(order[random(13)])+"「幽蘭空谷」"NOR"，$w看似隨意地一揮，從$n不可思議的角度攻入",
        "lvl" : 94,
        "skill_name" :  "幽蘭空谷"
]),
([        "action" : "$N使出"+(order[random(13)])+"「茶花滿路」"NOR"，一時間空中盡是$w的影子，令$n不知如何抵擋",
        "lvl" : 100,
        "skill_name" :  "茶花滿路"
]),
([        "action" : "$N一招"+(order[random(13)])+"「陌路採桑」"NOR"，$w連點數點，疾刺$n的$l",
        "lvl" : 99,
        "skill_name" :  "陌路採桑"
]),
([        "action" : "$N突然盤蹲下來，一招"+(order[random(13)])+"「秋雨蕭蕭」"NOR"，$w自下而上刺向$n",
        "lvl" : 106,
        "skill_name" :  "秋雨蕭蕭"
]),
([        "action" : "$N錯開腳步，手中$w突然從自己的肋下刺出，卻是一招"+(order[random(13)])+"「琴心劍膽」"NOR,
        "lvl" : 112,
        "skill_name" :  "琴心劍膽"
]),
([        "action" : "$N猶如在水面滑行一般，一招"+(order[random(13)])+"「池塘秋夜」"NOR"，平平地向$n的$l揮去",
        "lvl" : 118,
        "skill_name" :  "池塘秋夜"
]),
([        "action" : "$N一招"+(order[random(13)])+"「皓腕玉鐲」"NOR"，手中$w刺點$n的手腕",
        "lvl" : 124,
        "skill_name" :  "皓腕玉鐲"
]),
([        "action" : "$N一招"+(order[random(13)])+"「牡丹含淚」"NOR"，$w繞出數個銀圈，平平地向$n的$l卷去",
        "lvl" : 131,
        "skill_name" :  "牡丹含淚"
]),
([        "action" : "$N左腳輕點地面，身形往前一撲，一招"+(order[random(13)])+"「芍藥蘊珠」"NOR"，$w向$n的$l刺去",
        "lvl" : 138,
        "skill_name" :  "芍藥蘊珠"
]),
([        "action" : "$N一招"+(order[random(13)])+"「檐前飛燕」"NOR"，身形躍起，手中$w掃向$n的$l",
        "lvl" : 145,
        "skill_name" :  "檐前飛燕"
]),

([        "action" : "$N臉現黯然之色，隨意一招"+(order[random(13)])+"「蒹葭蒼蒼」"NOR"，$w刺向$n的$l",
        "lvl" : 159,
        "skill_name" :  "蒹葭蒼蒼"
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

        if ((int)me->query_skill("sword", 1) < 15)
                return notify_fail("你的基本劍法水平太低，無法學習玉女劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yunv-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的玉女劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -20;
        int d_e2 = 5;
        int p_e1 = -45;
        int p_e2 = -30;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 180;
        int m_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yunv-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<35 )
                return notify_fail("你的體力不夠練玉女劍法。\n");

        if( query("neili", me)<30 )
                return notify_fail("你的內力不足以練玉女劍法。\n");

        me->receive_damage("qi", 25);
        addn("neili", -20, me);

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"yunv-jian/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query("gender")== "女性")
                return 1.0;
        else
                return 0.7;
}

int help(object me)
{
        write(HIC"\n玉女劍法："NOR"\n");
        write(@HELP

    古墓派開山祖師林朝英自創劍法，不但劍招凌厲，而且講究豐
神脫俗、姿勢嫻雅，端的是美輪美奐、曼妙已極。

        學習要求：
                玉女心法15級
HELP
        );
        return 1;
}
