// haotian-zhang 昊天掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action" : "$N使一招"+(order[random(13)])+"「春江潮水」"NOR"，雙手劃了個半圈，按向$n的$l",
        "skill_name" : "春江潮水",
        "lvl" : 0
]),
([        "action" : "$N使一招"+(order[random(13)])+"「海上明月」"NOR"，左手輕輕一揮，劈向$n的$l",
        "skill_name" : "海上明月",
        "lvl" : 5
]),
([        "action" : "$N右手掌心向外，由右向左，使一招"+(order[random(13)])+"「灩灩隨波」"NOR"，向$n的$l打去",
        "skill_name" : "灩灩隨波",
        "lvl" : 10
]),
([        "action" : "$N使一招"+(order[random(13)])+"「江流宛轉」"NOR"，分擊$n的胸口和$l",
        "skill_name" : "江流宛轉",
        "lvl" : 15
]),
([        "action" : "$N使一招"+(order[random(13)])+"「月照花林」"NOR"，左右掌同時擊出，在空中突然左右掌方向互
變",
        "skill_name" : "月照花林",
        "lvl" : 20
]),
([        "action" : "$N左手不住晃動，右掌一招"+(order[random(13)])+"「空中流霜」"NOR"，向$n的$l打去",
        "skill_name" : "空中流霜",
        "lvl" : 25
]),
([        "action" : "$N左手變掌為啄，右掌立掌如刀，一招"+(order[random(13)])+"「汀上白沙」"NOR"，劈向$n的$l",
        "skill_name" : "汀上白沙",
        "lvl" : 30
]),
([        "action" : "$N左腳退後半步，右掌使一招"+(order[random(13)])+"「江天一色」"NOR"，橫揮向$n",
        "skill_name" : "江天一色",
        "lvl" : 35
]),
([        "action" : "$N一招"+(order[random(13)])+"「皎皎孤月」"NOR"，左掌先發而後至，右掌後發而先至",
        "skill_name" : "皎皎孤月",
        "lvl" : 40
]),
([        "action" : "$N雙掌縮入袖中，雙袖飛起掃向$n的$l，卻是一招"+(order[random(13)])+"「長江流水」"NOR"，儀
態瀟洒",
        "skill_name" : "長江流水",
        "lvl" : 45
]),
([        "action" : "$N左手虛按，右手劃道弧線使一招"+(order[random(13)])+"「白雲悠悠」"NOR"，向$n的$l插去",
        "skill_name" : "白雲悠悠",
        "lvl" : 50
]),
([        "action" : "$N雙手變掌做拳，向前向後劃弧，一招"+(order[random(13)])+"「青楓浦上」"NOR"擊向$n的$l",
        "skill_name" : "青楓浦上",
        "lvl" : 55
]),
([        "action" : "$N左手虛劃，右手變掌為鉤一記"+(order[random(13)])+"「樓月蜚回」"NOR"擊向$n的$l",
        "skill_name" : "樓月蜚回",
        "lvl" : 60
]),
([        "action" : "$N施出"+(order[random(13)])+"「玉戶簾中」"NOR"，右掌向外揮出，左掌同時攻向$n",
        "skill_name" : "玉戶簾中",
        "lvl" : 65
]),
([        "action" : "$N由臂帶手，在面前緩緩劃過，使一招"+(order[random(13)])+"「鴻雁長飛」"NOR"，揮向$n的$l",
        "skill_name" : "鴻雁長飛",
        "lvl" : 70
]),
([        "action" : "$N負身就地，右掌使一招"+(order[random(13)])+"「魚龍潛躍」"NOR"，自下而上向$n的$l擊去",
        "skill_name" : "魚龍潛躍",
        "lvl" : 75
]),
([        "action" : "$N右手由鉤變掌，雙手掌心向上，右掌向前推出一招"+(order[random(13)])+"「月華流照」"NOR"",
        "skill_name" : "月華流照",
        "lvl" : 80
]),
([        "action" : "$N右掌不住向外掃出，是一式"+(order[random(13)])+"「閒潭落花」"NOR"，左掌旋轉著向$n攻去",
        "skill_name" : "閒潭落花",
        "lvl" : 85
]),
([        "action" : "$N右手經腹前經左肋向前撇出，使一招"+(order[random(13)])+"「江水流春」"NOR"，向$n的$l錘去
",
        "skill_name" : "江水流春",
        "lvl" : 90
]),
([        "action" : "$N使一招"+(order[random(13)])+"「斜月沉沉」"NOR"，左掌連劃三個大圈，右掌從圈中穿出擊向$n
",
        "skill_name" : "斜月沉沉",
        "lvl" : 95
]),
([        "action" : "$N左手向上劃弧攔出，右手使一招"+(order[random(13)])+"「碣石瀟湘」"NOR"，手掌不住晃動，不
離$n頭頂方寸之間",
        "skill_name" : "碣石瀟湘",
        "lvl" : 100
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo=="chunyang-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練昊天掌必須空手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為太差，無法學昊天掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學昊天掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法水平有限，無法學昊天掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("haotian-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的昊天掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<45 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練昊天掌。\n");
        me->receive_damage("qi", 40);
        addn("neili", -25, me);
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
        int d_e1 = -40;
        int d_e2 = -20;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 190;
        int f_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("haotian-zhang", 1);
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
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"haotian-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n昊天掌："NOR"\n");
        write(@HELP

    昊天掌為全真派武功。
    可與純陽拳互備。

        學習要求：
                先天氣功20級
HELP
        );
        return 1;
}
