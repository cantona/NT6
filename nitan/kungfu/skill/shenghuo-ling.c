// This program is a part of NT MudLIB
// shenghuo-ling.c 聖火令法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N踏上一步，忽地在地上一坐，已抱住了$n小腿。十指扣住了$n小腿上的
‘中都’‘築賓’兩穴，$n只覺下半身痠麻難動，大吃一驚",
         "lvl" : 0
]),
([      "action" : "突然之間，$N身形晃動，同時欺近，手中$w往$n身上劃去。腳下不知如何
移動，身形早變。右手同時抓住$n後領，一抖之下，將$n向外遠遠擲了出去",
        "lvl" : 10
]),
([      "action" : "$N欺身直進，左手持$w向$n天靈蓋上拍落。便在這一瞬之間，$n滾身向左，
已然一拳打在$n腿上。$n一個踉蹌，$N橫過$w戳向$n後心",
        "lvl" : 20
]),
([      "action" : "$N忽地放手，手中那柄$w尾端向上彈起，拍的一響，正好打中$n手腕。",
        "lvl" : 30
]),
([      "action" : "$N忽然低頭，一個頭錘向$n撞來，$n不動聲色，向旁又是一讓，突覺胸口
一痛，已被$N手肘撞中",
        "lvl" : 40
]),
([      "action" : "$N手中$w急揮橫掃，突然連翻三個空心筋斗。$n不知對方是何用意，心想還是避之
為妙，剛向左踏開一步，眼前白光急閃，$N的$w已到右肩",
        "lvl" : 50
]),
([      "action" : "$N忽然低頭，一個頭錘向$n撞來，$n不動聲色，向旁又是一讓，突覺胸口
一痛，已被$N手肘撞中",
        "lvl" : 60
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (query("int", me) < 32)
                return notify_fail("你先天悟性不足，無法領會聖火令法。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的內功火候不到，無法學習聖火令法。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的基本劍法火候不到，無法學習聖火令法。\n");

        if (query("max_neili", me) < 2400)
                return notify_fail("你的內功修為不足，無法學習聖火令法。\n");

        if (me->query_str() < 35)
                return notify_fail("你現在膂力太差，無法學習聖火令法。\n");

        if (me->query_int() < 40)
                return notify_fail("你現在無法領悟聖火令法的要詣。\n");

        if (me->query_dex() < 35)
                return notify_fail("你現在身法太差，無法學習聖火令法。\n");

        if (me->query_skill("force", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("你的內功修為不足，無法領會更高深的聖火令法。\n");

        if (me->query_skill("shenghuo-ling", 1) > 200)
        {
                 if (me->query_skill("shenghuo-ling", 1) >
                     me->query_skill("shenghuo-shengong", 1))
                            return notify_fail("你的聖火神功水平有限，無法領會"
                                               "更高深的聖火令法。\n");
        }

        if (me->query_skill("sword", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的聖火令法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("shenghuo-ling", 1) < 180)
                return notify_fail("你還沒有掌握聖火令法中所有的奧妙，無法"
                                   "通過鍛鍊獲得提升。\n");

        if ((int)query("qi", me) < 80)
                return notify_fail("你的體力不夠練聖火令法。\n");

        if ((int)query("neili", me) < 80)
                return notify_fail("你的內力不夠練聖火令法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -70, me);

        return 1;
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenghuo-ling", 1);
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
                "damage_type" : random(2) ? "劈傷" : "刺傷",
        ]);
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me)
{
        if( me->query_skill("qiankun-danuoyi", 1) < 100) return 1.0;
        if( me->query_skill("qiankun-danuoyi", 1) > 250) return 2.0;
        return (me->query_skill("qiankun-danuoyi", 1)-100)/150+1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (query_temp("shenghuo-ling/max_hit", me))
        {
                victim->receive_wound("qi", damage_bonus);
                return HIR "只聽“噗嗤”一聲，一股鮮血至$n" HIR "胸前射出！"
                       "\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-ling/" + action;
}

int help(object me)
{
        write(HIR"\n聖火令法："NOR"\n");
        write(@HELP

    聖火令法是明教聖物聖火令上的武功，以其招式怪異無比而往
打之措手不及，加上聖火令之特殊性，更是厲害無比。

        學習要求：
                九陽神功20級
                內力50
                太監無法修習50級以上的聖火令法
HELP
        );
        return 1;
}