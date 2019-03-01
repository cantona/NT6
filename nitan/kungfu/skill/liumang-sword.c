
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": HIW "$N大喝一聲，一招「流氓霸市」，手中$w平空橫掃，一條劍氣劃向$n的$l" NOR,
        "force" : 25,
        "dodge" : 20,
        "parry" : 25,
        "lvl"   : 0,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N向前跨上一步，右手$w使出一式「雷劍閃」直刺$n的$l" NOR,
        "force" : 30,
        "dodge" : 25,
        "parry" : 30,
        "lvl"   : 6,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N身形往右一挫，右手$w使出一式「沖心劍」刺向$n的$l" NOR,
        "force" : 30,
        "dodge" : 35,
        "parry" : 35,
        "lvl"   : 12,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N雙膝下沉，右手$w使出一式「鎖喉式」，由下而上疾刺$n的$l" NOR,
        "force" : 35,
        "dodge" : 35,
        "parry" : 40,
        "lvl"   : 15,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N一招「車輪劍」，$w自上而下劃出一個大弧，平平地向$n的$l揮去" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 45,
        "lvl"   : 18,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N上身往左側一擰，一招「惡龍擺尾」，右手$w反手向$n的$l揮去" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 55,
        "lvl"   : 21,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N一招「摧心式」，劍鋒平指，一氣呵成橫掃$n的$l" NOR,
        "force" : 40,
        "dodge" : 60,
        "parry" : 55,
        "lvl"   : 24,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N左腿提膝，手中$w斜指，一招「破目式」刺向$n的$l" NOR,
        "force" : 40,
        "dodge" : 55,
        "parry" : 60,
        "lvl"   : 27,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N一招「回龍式」，$w自下而上劃出一個大弧，平平地揮向$n的$l" NOR,
        "force" : 45,
        "dodge" : 65,
        "parry" : 65,
        "lvl"   : 30,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N使出「套月式」，$w劃出三個圓圈，劍鋒直出，綿綿不斷劃向$n的$l" NOR,
        "force" : 45,
        "dodge" : 70,
        "parry" : 70,
        "lvl"   : 35,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N一招「卷風式」，$w輕靈地劃出幾個圓弧，迅速地向$n的$l揮去" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 40,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N一招「抱頭式」，$w劃出一個左低右高的大弧，斜斜地斬向$n的$l" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 45,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N使出「纏絲式」，$w由右向左劃出一個大８字，將$n圈在其中" NOR,
        "force" : 55,
        "dodge" : 85,
        "parry" : 80,
        "lvl"   : 50,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N左腳踏實，右腳虛點，一招「惡人指路」，右手$w帶著一團劍花，逼向$n的$l" NOR,
        "force" : 55,
        "dodge" : 95,
        "parry" : 80,
        "lvl"   : 60,
        "damage_type" : "刺傷"
]),
([  "action" : HIC "$N回身擰腰，右手虛抱，一招「天人同滅」，$w中宮直進，刺向$n的$l" NOR,
        "force" : 950,
        "attack": 1140,
        "dodge" : 2220,
        "parry" : 2220,
        "damage": 1140,
        "lvl" : 2500,
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候太淺。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("liumang-sword", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("liumang-sword", 1) < 100 ||
            !(m_weapon=query_temp("weapon", me)) || 
            query("skill_type", m_weapon) != "sword" )
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("sword", 1) / 2 +
             me->query_skill("liumang-sword", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一抖手中的" + m_weapon->name() +
                                            HIC "，劃出了一個圓圈，竟然讓$N" +
                                            HIC "的攻擊全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "晃動手中的" + m_weapon->name() +
                                            HIC "，不住的變幻劍勢，讓$N"
                                            HIC "完全無法捕捉到力道。\n" NOR]);
                        break;
                }
                return result;
        }
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        me->receive_damage("qi", 50);
        addn("neili", -64, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-sword/" + action;
}