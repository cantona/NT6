// tiangang-zhi.c 天罡指穴法

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N左手輕輕撥動，右手五指徐徐彈出撥，一式"CYN"「浪起湖心」"NOR"，拂向$n的$l",
        "lvl" : 0,
        "skill_name" : "浪起湖心"
]),
([        "action" : "$N雙手上下起落，俯身掠向$n，一式"HIC"「瀑落清潭」"NOR"，左手化掌成指，洶湧襲向$n的$l",
        "lvl" : 12,
        "skill_name" : "瀑落清潭"
]),
([        "action" : "$N左手由拳變掌，右手扭曲如靈蛇，一式"BLU"「龜蛇競渡」"NOR"，左右並用，拍向$n的$l",
        "lvl" : 24,
        "skill_name" : "龜蛇競渡"
]),
([        "action" : "$N一式"YEL"「倒索攀山」"NOR"，左手抽回，右手前探，戟指點向$n的$l",
        "lvl" : 36,
        "skill_name" : "倒索攀山"
]),
([        "action" : "$N使一式"MAG"「閃現雷鳴」"NOR"，身影變幻不定地掠至$n身後，猛地拍向$n的$l",
        "lvl" : 48,
        "skill_name" : "閃現雷鳴"
]),
([        "action" : "$N兩臂大開大闔，吸一口氣，一式"HIB"「地動山搖」"NOR"，勁力透徹，雙手快速一撥，激出數道勁氣逼向$n的$l",
        "lvl" : 60,
        "skill_name" : "地動山搖"
]),
([        "action" : "$N身形縱起，衣袂飄蕩，雙手輕輕拍動，一式"HIW"「水拍雲崖」"NOR"，居高臨下，連綿不絕拍向$n的$l",
        "lvl" : 72,
        "skill_name" : "水拍雲崖"
]),
([        "action" : "$N騰空而起，雙掌合一，十指如鈎，一招"HIY"「泰山壓頂」"NOR"，疾向$n的擊落，勢道兇猛已極",
        "lvl" : 84,
        "skill_name" : "泰山壓頂"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) { return combo == "jinding-zhang" || combo == "jieshou-jiushi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HIC"練天罡指穴法必須空手。\n"NOR);

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學天罡指穴法。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練天罡指穴法。\n");

        if (me->query_skill("finger", 1) < me->query_skill("tiangang-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的天罡指穴法。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了，無法練天罡指穴法。\n");
        if( query("neili", me)<25 )
                return notify_fail("你的內力不夠練天罡指穴法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e1 = 30;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -10;
        int f_e1 = 260;
        int f_e2 = 360;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tiangang-zhi", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"tiangang-zhi/" + action;
}

int help(object me)
{
        write(HIC"\n天罡指穴法："NOR"\n");
        write(@HELP

    天罡指穴法為峨嵋派武功。
    可與金頂綿掌互備。

        學習要求：
                臨濟十二莊20級
                內力100
HELP
        );
        return 1;
}
