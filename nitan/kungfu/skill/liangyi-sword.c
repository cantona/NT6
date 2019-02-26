// liangyi-sword.c (kunlun) 崑崙派正兩儀劍法
// Last Modified by sir 10.22.2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action= ({ // 12 招
([        "action":"$N一式"HIC"「順水推舟」"NOR"，$N手中$w指向自己左胸口，劍柄斜斜向右外，緩緩划向$n的$l",
        "lvl" : 0,
        "skill_name" : "順水推舟"
]),
([        "action":"$N身形微側，左手後襬，右手$w一招"HIY"「橫掃千軍」"NOR"，直向$n的腰間揮去",
        "lvl" : 10,
        "skill_name" : "橫掃千軍"
]),
([        "action":"$N縱身近前，$w斗然彎彎彈出，劍光爆長，一招"HIB"「峭壁斷雲」"NOR"，猛地刺向$n的胸口",
        "lvl" : 20,
        "skill_name" : "峭壁斷雲"
]),
([        "action":"$N左手捏個劍決，平推而出，決指上仰，右手劍朝天不動，一招"MAG"「仙人指路」"NOR"，刺向$n",
        "lvl" : 30,
        "skill_name" : "仙人指路"
]),
([        "action":"$N劍招忽變，使出一招"GRN"「雨打飛花」"NOR"，全走斜勢，但七八招斜勢中偶爾又挾着一招正勢，教人極難捉摸",
        "lvl" : 40,
        "skill_name" : "雨打飛花"
]),
([        "action":"$N手中$w劍刃豎起，鋒口向下，一招"BLU"「大漠平沙」"NOR"，劍走刀勢，劈向$n的$l",
        "lvl" : 50,
        "skill_name" : "大漠平沙"
]),
([        "action":"$N一招"YEL"「木葉蕭蕭」"NOR"，$N橫提$w，劍尖斜指向天，由上而下，劈向$n的$l",
        "lvl" : 60,
        "skill_name" : "木葉蕭蕭"
]),
([        "action":"$N搶前一步，$w微微抖動，劍光點點，一招"HIC"「江河不竭」"NOR"，終而復始，綿綿不絕刺向$n",
        "lvl" : 70,
        "skill_name" : "江河不竭"
]),
([        "action":"$N左手劍鞘一舉，快逾電光石光，一招"HIW"「高塔掛雲」"NOR"，用劍鞘套住$n手中兵器，$w直指$n的咽喉",
        "lvl" : 80,
        "skill_name" : "高塔掛雲"
]),
([        "action":"$N翻身回劍，劍訣斜引，一招"HIM"「百丈飛瀑」"NOR"，劍鋒從半空中直瀉下來，罩住$n上方",
        "lvl" : 90,
        "skill_name" : "百丈飛瀑"
]),
([        "action":"$N一式"HIB"「雪擁藍橋」"NOR"，$N手中劍花團團，一條白練疾風般向卷向$n",
        "lvl" : 100,
        "skill_name" : "雪擁藍橋"
]),
([        "action":"$N騰空而起，突然使出一招"HIW"「無聲無色」"NOR"，悄無聲息地疾向$n的背部刺去",
        "lvl" : 130,
        "skill_name" : "無聲無色"
]),
});

int valid_enable(string usage) { return (usage=="sword") || (usage=="parry"); }
int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 100)
                return notify_fail("你的玄天無極功火候太淺。\n");
        if ((int)me->query_skill("xunlei-sword", 1) < 80)
                return notify_fail("你的迅雷十六劍火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("liangyi-sword", 1);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<35 || query("neili", me)<15 )
                return notify_fail("你的內力或氣不夠練兩儀劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
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
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -5;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 60;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liangyi-sword", 1);
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
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liangyi-sword/" + action;
}
/*mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int i;

        i=me->query_skill("liangyi-sword",1)/3;
        if( query_temp("ly_hebi", me) && !query_temp("hebi_hit", me )
                && me->query_skill_mapped("parry") == "liangyi-sword")
        {
                set_temp("hebi_hit", 1, me);
                addn_temp("apply/attack", i, me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                addn_temp("apply/attack", -i, me);
                delete_temp("hebi_hit", me);
        }
}*/
int double_attack() { return 1; }
int help(object me)
{
        write(HIC"\n正兩儀劍法："NOR"\n");
        write(@HELP

    正兩儀劍法是崑崙派的高深劍法。
    倘若雙劍合璧，兩儀化四象，四象生八卦，陰陽相調，水火互
濟，威力很強！

        學習要求：
                玄天無極功100級
                迅雷十六劍80級
                內力800
HELP
        );
        return 1;
}

