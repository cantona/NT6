// ruyi-hook.c 如意鉤法
// Last Modifyed by Winder on Aug. 21 2002

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "只見$N$w望空一點，一招「翻天覆地」同時攻向$n的頭部，左腿橫出，掃向$n腿部。",
        "lvl" : 0,
        "skill_name" : "翻天覆地"
]),
([        "action" : "只見$N左手劍指虛攻$n的上身，$w卻以迅雷不及掩耳之勢向$n的腰部鉤去。好一招「若離若合」！",
        "lvl" : 3,
        "skill_name" : "若離若合"
]),
([        "action" : "只見$N一招「雪滿銀鉤」將$w舞得如同雪花紛飛，將$n的全身籠罩在$w光芒之下。",
        "lvl" : 6,
        "skill_name" : "雪滿銀鉤"
]),
([        "action" : "只見$N使出「天王索命」，一鉤緊似一鉤，一鉤快似一勾，一氣呵成，直逼$n的周身大穴。",
        "lvl" : 9,
        "skill_name" : "天王索命"
]),
([        "action" : "$N一招「天馬行空」，$w自上而下劃出一個大弧，平平地向$n的$l揮去",
        "lvl" : 12,
        "skill_name" : "天馬行空"
]),
([        "action" : "$N一招「神龍擺尾」，右腳虛上，右手回收，$w向下截劈$n的$l",
        "lvl" : 15,
        "skill_name" : "神龍擺尾"
]),
([        "action" : "$N一招「鉤心鬥角」，$w自左而右，一氣呵成橫掃$n的$l",
        "lvl" : 18,
        "skill_name" : "鉤心鬥角"
]),
([        "action" : "$N右腳向前一步，左膝提起，一招「不陰不陽」，$w向前上方刺向$n的$l",
        "lvl" : 21,
        "skill_name" : "不陰不陽"
]),
([        "action" : "$N使一招「爾虞我詐」，右腳向後回撤，$w隨身體右後撤，突然向左前方刺向$n的$l",
        "lvl" : 24,
        "skill_name" : "爾虞我詐"
]),
([        "action" : "$N使出「峰巒重疊」，$w劃出三個圓弧，綿綿不斷劃向$n的$l",
        "lvl" : 27,
        "skill_name" : "峰巒重疊"
]),
([        "action" : "$N一轉身，$w向後斜帶，一招「飛橫拔戶」，砍向$n的$l",
        "lvl" : 30,
        "skill_name" : "飛橫拔戶"
]),
([        "action" : "$N雙手握著$w，微一低頭，一招「閉門思過」，突然從腦後疾向$n刺去",
        "lvl" : 35,
        "skill_name" : "閉門思過"
]),
([        "action" : "$N雙手執著$w，鉤頭向內，一招「欲擒故縱」，倒轉身體，刺向$n",
        "lvl" : 40,
        "skill_name" : "欲擒故縱"
]),
([        "action" : "$N一招「對牛彈琴」，$w在$n一楞之間突然劃向$n的$l",
        "lvl" : 50,
        "skill_name" : "對牛彈琴"
]),
([        "action" : "$N雙腳並步，身體立起，一招「蓮葉托桃」，$w向前平刺$n的襠部",
        "lvl" : 60,
        "skill_name" : "蓮葉托桃"
]),
([        "action" : "$N一招「群魔亂舞」，$w舞動護住全身向$n撞去",
        "lvl" : 70,
        "skill_name" : "群魔亂舞"
]),
([        "action" : "$N一反身，使一招「魚死網破」，$w不顧一切地劈向$n的$l",
        "lvl" : 80,
        "skill_name" : "魚死網破"
]),
([        "action" : "$N右手$w向後撤，再向前平平托起，一招「描龍繡鳳」刺向$n的$l",
        "lvl" : 90,
        "skill_name" : "描龍繡鳳"
]),
([        "action" : "$N身子向上縱起，一招「天地同壽」，頭下腳上，$w向$n的頭頂刺去",
        "lvl" : 100,
        "skill_name" : "天地同壽"
]),
});


int valid_enable(string usage) { return (usage == "hook") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 20)
                return notify_fail("你的毒龍大法火候太淺。\n");
        if ((int)me->query_skill("hook", 1) < 20)
                return notify_fail("你的鉤法基本功還不紮實。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "hook" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的氣血不夠練如意鉤法。\n");
        me->receive_damage("qi", 30);
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 100;
        int f_e2 = 200;
        int m_e1 = 200;
        int m_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("ruyi-hook",1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"ruyi-hook/" + action;
}

int help(object me)
{
        write(HIC"\n如意鉤法"NOR"\n");
        write(@HELP

    如意鉤法是神龍島鉤法。

        學習要求：
                毒龍大法20級
                基本鉤法20級
                內力修為100
HELP
        );
        return 1;
}
