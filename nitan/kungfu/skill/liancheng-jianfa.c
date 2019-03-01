// This program is a part of NITAN MudLIB
// liancheng-jian.c 連城劍法

inherit SKILL;

string *action_msg = ({
        "$N使一式「孤鴻海上來」，手中$w嗡嗡微振，幻成一條疾光刺向$n的$l",
        "$N錯步上前，使出「池潢不敢顧」，手中$w劃出一道劍光劈向$n的$l",
        "$N手中$w一抖，一招「落日照大旗」，斜斜一劍反腕撩出，攻向$n的$l",
        "$N手中劍鏘啷啷長吟一聲，一式「馬鳴風蕭蕭」，一道劍光飛向$n的$l",
        "$N一式「落日陽關路」，手中$w舞出無數劍花，使$n難斷虛實，無可躲避",
        "$N手中$w斜指蒼天，劍芒吞吐，一式「羌笛怨楊柳」，對準$n的$l斜斜擊出",
        "$N一式「春風度玉門」，手腕急抖，揮洒出萬點金光，刺向$n的$l",
        "$N一式「遙掛在前川」，$w飛斬盤旋，如疾電般射向$n的胸口",
        "$N一式「飛流三千尺」，$w突然從天而降，一片金光圍掠$n全身",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me) { return 1; }

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(60),
                "attack": 70 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"刺傷":"割傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練連城劍法。\n");
        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠。\n");
        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liancheng-jianfa/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("liancheng-jianfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}