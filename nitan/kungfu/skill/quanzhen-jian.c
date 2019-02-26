// quanzhen-sword.c 全真劍法
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N意帶神閒，一式"GRN"「分花拂柳」"NOR"，$w輕輕飛動，幻起一片劍光，圍掠$n全身",
        "lvl" : 0,
        "skill_name" : "分花拂柳"
]),
([        "action":"$N使一招"HIY"「琴心三疊」"NOR"，身形向上飄起，手中$w虛虛實實幻出三點寒光射向$n$l",
        "lvl" : 9,
        "skill_name" : "琴心三疊"
]),
([        "action":"$N身形一轉，猛然一式"HIG"「罡風掃葉」"NOR"，舞出滿天劍影，挾着勁風向$n的$l掃去",
        "lvl" : 18,
        "skill_name" : "罡風掃葉"
]),
([        "action":"$N仰天長笑，身形飄然而起，在半空中身子一旋，一式"HIM"「狂歌痛飲」"NOR"狂風般地擊向$n",
        "lvl" : 27,
        "skill_name" : "狂歌痛飲"
]),
([        "action":"$N左手捏着劍訣，右足踏開一招"RED"「定陽針」"NOR"向上斜刺，長劍鏘然躍出倏的化作幾點星光射向$n的$l",
        "lvl" : 36,
        "skill_name" : "定陽針"
]),
([        "action":"$N向前邁去一大步，使出"HIB"「探海屠龍」"NOR"，手中$w舞成一個光球，迅若奔雷擊向$n的$l",
        "lvl" : 45,
        "skill_name" : "探海屠龍"
]),
([        "action":"$N運力一抖$w，一時"HIM"「馬蹴落花」"NOR"，$w幻出點點劍花，飄然刺向$n的$l",
        "lvl" : 54,
        "skill_name" : "馬蹴落花"
]),
([        "action":"$N手中$w斜指蒼天，縱起丈餘，一時"YEL"「橫行漠北」"NOR"，$w雷霆般射向$n的$l",
        "lvl" : 63,
        "skill_name" : "橫行漠北"
]),
([        "action":"$N大喝一聲，一招"HIW"「白虹經天」"NOR"，$w閃電般劃出一道大圓弧劈向$n的$l",
        "lvl" : 72,
        "skill_name" : "白虹經天"
]),
([        "action":"$N身形向上飄起，突然一轉身，頭下腳上，手握$w，一招"HIW"「絮墜無聲」"NOR"，無聲無息地攻向$n的$l",
        "lvl" : 81,
        "skill_name" : "絮墜無聲"
]),
([        "action":"$N手中$w一抖，一招"HIR"「照破萬緣」"NOR"，$w逼出耀眼光芒，奮力擊向$n的$l",
        "lvl" : 90,
        "skill_name" : "照破萬緣"
]),
([        "action":"$N忽然身形高高躍起，使出"HIC"「浪跡天涯」"NOR"，$w幻出漫天花瓣，迅如雷霆射向$n的$l",
        "lvl" : 150,
        "skill_name" : "浪跡天涯"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不足，無法學習全真劍法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為太差，無法學習全真劍法。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法修為不夠，無法學習全真劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("quanzhen-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的全真劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<55 )
                return notify_fail("你的體力不夠練全真劍法。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不足以練全真劍法。\n");
        me->receive_damage("qi", 50);
        addn("neili", -35, me);
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
        int d_e2 = 0;
        int p_e1 = -50;
        int p_e2 = -30;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 190;
        int m_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("quanzhen-jian", 1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("xiantian-qigong",1) > 10) return 1.0;
        else return 0.6;
}

string perform_action_file(string action)
{
        return __DIR__"quanzhen-jian/" + action;
}
int help(object me)
{
        write(HIC"\n全真劍法："NOR"\n");
        write(@HELP

    全真劍法以法度嚴謹、招式狠辣著稱，創派祖師王重陽少年時
仗此劍法誅殺奸邪，韃子聞風喪膽。

        學習要求：
                先天氣功或玉女心法25級
                內力100
HELP
        );
        return 1;
}
