#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action": "$N左手$w輕送，一招" +(order[random(13)])+"「朝天勢」"NOR"向前刺出,疾刺$n的$l",
        "lvl" : 0,
        "skill_name" : "朝天勢"
]),
([        "action": "$N疾步上前，劍尖連連點出，一式"+(order[random(13)])+"「天雪九點」"NOR"，$n正瞧得眼花繚亂，手忙足亂之際，\n突然間$l被一劍刺中",
        "lvl" : 10,
        "skill_name" : "天雪九點"
]),
([        "action": "$N劍尖倏地翻上，斜刺$n的$l，正是雪山派劍法中的"+(order[random(13)])+"「老枝橫斜」"NOR"",
        "lvl" : 30,
        "skill_name" : "老枝橫斜"
]),
([        "action":  "$N劍尖一抖，正當$n意欲招架，$N不再和他兵刃相碰，立時變招，帶轉劍鋒，\n斜削敵喉，正是雪山派劍法中的"+(order[random(13)])+"「雪泥鴻爪」"NOR"",
        "lvl" : 50,
        "skill_name" : "雪泥鴻爪"
]),
([        "action": "$N手中$w一招" +(order[random(13)])+"「暗香疏影」"NOR"，如流光逸影，劍刃若有若無，斜削過來，$n難以抵擋，被一劍削中$l",
        "lvl" : 80,
        "skill_name" : "暗香疏影"
]),
([        "action": "$N手中$w連劃五個圈子，一招"+(order[random(13)])+"「朔風忽起」"NOR"，五道劍芒如罡風呼嘯，向$n疾刮而去",
        "lvl" : 110,
        "skill_name" : "朔風忽起"
]),
([        "action": "$N一式" +(order[random(13)])+"「明駝西來」"NOR"，手中$w看似沉滯不堪，卻似慢實快，令$n難斷虛實，無可躲避",
        "lvl" : 130,
        "skill_name" : "明駝西來"
]),
([        "action": "$N忽然收劍回劃，一式" +(order[random(13)])+"「飛沙走石」"NOR"，猛地激起地上落葉飛石四處飛揚，挾無比威勢，向$n$l刺去",
        "lvl" : 150,
        "skill_name" : "飛沙走石"
]),
([        "action": "$N舉劍和身躍出，一式" +(order[random(13)])+"「胡馬越嶺」"NOR"，$w幻出萬道劍芒，于劍光中疾取$n的$l",
        "lvl" : 150,
        "skill_name" : "胡馬越嶺"
]),
([        "action": "$N左手緊握劍指，右劍默運冰雪心法，劍上隱隱青氣透出，一式"+(order[random(13)])+"「嶺上雙梅」"NOR"，\n劍指劍鋒左右夾攻，直逼$n$l",
        "lvl" : 160,
        "skill_name" : "嶺上雙梅"
]),
([        "action": "$N一式" +(order[random(13)])+"「明月羌笛」"NOR"，$w劃了一個半月弧形，洒出點點銀光，飛向$n的$l",
        "lvl" : 160,
        "skill_name" : "明月羌笛"
]),
([        "action": "$N一招" +(order[random(13)])+"「月色黃昏」"NOR"，使得若有若無，朦朦朧朧，$w斜斜劃出，直取$n$l",
        "lvl" : 170,
        "skill_name" : "月色黃昏"
]),
([        "action": "$N手中$w抖動，一招" +(order[random(13)])+"「梅雪爭春」"NOR"，虛中有實，實中有虛，劍尖劍鋒齊用，\n劍尖是雪點，劍鋒乃格枝，四面八方的向$n攻了過來",
        "lvl" : 180,
        "skill_name" : "梅雪爭春"
]),
([        "action": "$N手中$w甩出，一招" +(order[random(13)])+"「鶴飛九天」"NOR"，在空中盤旋回饒，如閃電般向$n刺出九九\n八十一劍，然後飛回$N手中",
        "lvl" : 190,
        "skill_name" : "鶴飛九天"
]),
([        "action": "$N長嘯一聲，身法加快，一招"+(order[random(13)])+"「暗影浮香」"NOR"，$w如梅幹彎彎遞出，$n正驚疑間，\n劍上突然豪光綻放,道道劍氣向$n籠罩而去",
        "lvl" : 200,
        "skill_name" : "暗影浮香"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不到，無法學習雪山劍法。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太差，無法學習雪山劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候太淺，無法學習雪山劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("xueshan-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的雪山劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -15;
        int d_e2 = -10;
        int p_e1 = -40;
        int p_e2 = -25;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 170;
        int m_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xueshan-jian", 1);
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

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練雪山劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練雪山劍法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xueshan-jian/" + action;
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n雪山劍法："NOR"\n");
        write(@HELP

    雪山劍法為雪山派本門劍法。

        學習要求：
                內力50
HELP
        );
        return 1;
}
