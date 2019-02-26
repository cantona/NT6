#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙手平伸，向外掠出，一式"GRN"「春雲乍展」"NOR"，指尖輕盈漂動，輕輕反點$n的$l",
        "lvl" : 10,
        "skill_name" : "春雲乍展"
]),
([        "action" : "$N右手五指緩緩一收，一式"HIG"「迴風拂柳」"NOR"，五指忽然遙遙拂向$n，$n只覺得五股疾風襲向自己五處大穴",
        "lvl" : 0,
        "skill_name" : "迴風拂柳"
]),
([        "action" : "$N突然縱身躍入半空，一個輕巧轉身，單掌劈落，一式"MAG "「江城飛花」"NOR"，拍向$n的頭頂",
        "lvl" : 10,
        "skill_name" : "江城飛花"
]),
([        "action" : "$N突然躍起，雙手連環，運掌如劍，勢如疾風電閃，一式"HIM "「雨急風狂」"NOR"，攻向$n的全身",
        "lvl" : 10,
        "skill_name" : "雨急風狂"
]),
([        "action" : "$N左手揮起，掌心朝天，伸出右手併攏食指中指，捻個劍決，一式"CYN"「星河在天」"NOR"，直指$n的中盤",
        "lvl" : 20,
        "skill_name" : "星河在天"
]),
([        "action" : "$N突然抽身而退，接着一式"HIW"「流華紛飛」"NOR"，平身飛起，雙掌向$n的後腦連拍數掌",
        "lvl" : 30,
        "skill_name" : "流華紛飛"
]),
([        "action" : "$N突然抽身躍起，左掌挾着勁風洶湧拍出，接着右掌自左掌後突地伸出，一式"HIR"「彩雲追月」"NOR"搶在左掌前向$n的$l拍去",
        "lvl" : 30,
        "skill_name" : "彩雲追月"
]),
([        "action" : "$N使一式"HIC"「天如穹廬」"NOR"，全身突然飛速旋轉，雙掌忽前忽後，猛地拍向$n的胸口",
        "lvl" : 40,
        "skill_name" : "天如穹廬"
]),
([        "action" : "$N前後一揉，一式"HIB"「朝雲橫度」"NOR"，化掌如劍，一股凌厲劍氣襲向$n的下盤",
        "lvl" : 50,
        "skill_name" : "朝雲橫度"
]),
([        "action" : "$N使一式"HIW"「白虹經天」"NOR"，雙掌舞出無數圈勁氣，一環環向$n的$l斫去",
        "lvl" : 70,
        "skill_name" : "白虹經天"
]),
([        "action" : "$N雙手食指和中指一和，一式"HIM"「紫氣東來」"NOR"，一股強烈的氣流湧向$n的全身",
        "lvl" : 60,
        "skill_name" : "紫氣東來"
]),
([        "action" : "$N一式"HIC"「落英漫天」"NOR"，雙掌在身前疾轉，掌花飛舞，鋪天蓋地直指向$n。$n只見漫天掌花，眼花繚亂。",
        "lvl" : 99,
        "skill_name" : "落英漫天"
])
});
/*
mapping *action = ({
([      "action" : "$N右手五指緩緩一收，一式「迴風拂柳」，五指忽然拂向$n五處大穴",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "內傷",
        "skill_name"  : "迴風拂柳"
]),
([      "action" : "$N陡然一個輕巧轉身，單掌劈落，一式「江城飛花」，拍向$n的頭頂",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "瘀傷",
        "skill_name"  : "江城飛花"
]),
([      "action" : "$N突然躍起，雙手連環，運掌如劍，一式「雨急風狂」，攻向$n的全身",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "瘀傷",
        "skill_name"  : "雨急風狂"
]),
([      "action" : "$N突然抽身而退，一式「流華紛飛」，平身飛起，雙掌向$n連拍數掌",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "瘀傷",
        "skill_name"  : "流華紛飛"
]),
([      "action" : "$N突然抽身躍起，右掌翻滾，一式「彩雲追月」搶在左掌前向$n的$l拍去",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "彩雲追月"
]),
([      "action" : "$N使一式「白虹經天」，雙掌舞出無數圈勁氣，一環環向$n的$l斫去",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "內傷",
        "skill_name"  : "白虹經天"
]),
([      "action" : "$N一式「落英漫天」，雙掌在身前疾轉，掌花飛舞，鋪天蓋地直指向$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "落英漫天"
]),
//新增三招
([      "action" : "[1;32m$N一式「柳吉祥」，雙掌如柳絮般在胸前擺動，頓時一道道暗勁快速衝向$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "內傷",
        "skill_name"  : "[1;32m柳吉祥[2;37;0m"
]),
([      "action" : "[1;37m$N的落英神掌已修煉至大成，一招「弧月斬」，猛然凌空飛起，當頭向$n斬去[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "內傷",
        "skill_name"  : "[1;37m弧月斬[2;37;0m"
]),
([      "action" : "[1;36m$N的落英神掌已入返璞歸真境界，運起全身內力，一招「碧濤頌」，如海浪般的

內力向$n湧去，頓時三丈範圍內沙石飛旋，眼見$n已無處可逃[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "內傷",
        "skill_name"  : "[1;36m碧濤頌[2;37;0m"
])
});
*/
int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練落英神劍掌必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的基本內功火候不夠，無法學落英神劍掌。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太弱，無法練落英神劍掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的落英神劍掌。\n");

        /*
        if( query("character", me) == "陰險奸詐" )
                return notify_fail("學習落英神劍掌需要博大的胸懷，沒有此等胸懷是無法領悟的。\n");
        */

        if( query("str", me)<22 )
                return notify_fail("你先天臂力不足，無法修煉落英神劍掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不夠嫻熟，無法修煉落英神劍掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不夠嫻熟，無法修煉落英神劍掌。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -35;
        int d_e2 = -15;
        int p_e1 = -45;
        int p_e2 = -35;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenzhang", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<300 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練落英神劍掌。\n");

        me->receive_damage("qi", 45);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n落英神劍掌："NOR"\n");
        write(@HELP

    落英神劍掌脱胎於落英神劍，以掌代劍，威力不遜。
    可與旋風掃葉腿互備。

        學習要求：
                碧波神功15級
                內力100
HELP
        );
        return 1;
}
