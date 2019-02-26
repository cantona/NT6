//huifeng-jian.c 迴風拂柳劍

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name":   "清風襲月",
        "action" : "$N劍尖劍芒暴長，一招"HIC"「清風襲月」"NOR"，手中$w自左下大開大闔，一劍向右上向$n的$l",
        "lvl" : 0
]),
([        "skill_name":   "飄雪穿雲",
        "action" : "$N長劍圈轉，一招"HIW"「飄雪穿雲」"NOR"，手中$w平展下刺，一劍輕輕劃過$n的$l",
        "lvl" : 10
]),
([        "skill_name":   "千峯競秀",
        "action" : "$N長劍輕靈跳動，劍隨身長，右手$w使出一式"GRN"「千峯競秀」"NOR"刺向$n的$l",
        "lvl" : 20
]),
([        "skill_name":   "萬流歸宗",
        "action" : "$N長劍下指，劍意流轉，一招"HIB"「萬流歸宗」"NOR"直取$n的$l",
        "lvl" : 30
]),
([        "skill_name":   "烏龍攪柱",
        "action" : "$N劍芒吞吐，幻若靈蛇，右手$w使出一式"BLU"「烏龍攪柱」"NOR"，劍勢曼妙，刺向$n的$l",
        "lvl" : 40
]),
([        "skill_name":   "大雁啼沙",
        "action" : "$N屈腕雲劍，劍光如彩碟紛飛，幻出點點星光，右手$w使出一式"HIY"「大雁啼沙」"NOR"躍躍灑灑飄向$n的$l",
        "lvl" : 50
]),
([        "skill_name":   "進退龍遊",
        "action" : "$N揮劍分擊，劍勢自胸前躍出，右手$w一式"HIM"「進退龍遊」"NOR"，毫無留戀之勢，刺向$n的$l",
        "lvl" : 60
]),
([        "skill_name":   "天地鶴翔",
        "action" : "$N退步，左手劍指劃轉，腰部一扭，右手$w一記"MAG"「天地鶴翔」"NOR"自下而上刺向$n的$l",
        "lvl" : 70
]),
});

int valid_enable(string usage) { return (usage=="sword") || (usage=="parry") ; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候太淺。\n");

        if (me->query_skill("sword", 1) < me->query_skill("huifeng-jian"))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的迴風拂柳劍。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<35 )
                return notify_fail("你的內力或氣不夠練迴風拂柳劍。\n");
        me->receive_damage("qi", 45);
        addn("neili", -30, me);
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
        int d_e1 = -10;
        int d_e2 = 10;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 160;
        int m_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huifeng-jian", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"huifeng-jian/" + action;
}

int help(object me)
{
        write(HIC"\n迴風拂柳劍："NOR"\n");
        write(@HELP

    迴風拂柳劍為峨嵋派武功。

        學習要求：
                臨濟十二莊20級
                內力50
HELP
        );
        return 1;
}
