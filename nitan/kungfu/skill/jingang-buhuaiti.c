// jingang-buhuaiti.c

#include <ansi.h>

inherit SHAOLIN_SKILL;

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以修習這等神功。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力還不足以修習這等神功。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("jingang-buhuaiti", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的金剛不壞體神功。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("jingang-buhuaiti", 1) < 200 ||
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1) * 12;
        ap=ob->query_skill("force")*12+query("max_neili", ob)+mp;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(5))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "身前彷彿有一道無形氣牆，讓$N"
                                            HIY "再難前進一步。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "只見$N" HIY "這一招打了個正中！然而$n"
                                            HIY "毫不在意，並沒有放在心上。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIY "$N" HIY "一招正好打在$n" HIY "身上，可"
                                            "力量猶如石沉大海，絲毫不起作用。\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIY "$N" HIY "一招擊在$n" HIY "身上，可聽$n"
                                            HIY "一聲大喝，$N" HIY "反被護體罡氣震退了"
                                            "數步。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "渾若無事的接下了$N"
                                            HIY "這一招，卻沒有受到半點傷害。\n" NOR]);
                        break;
                }
                return result;
        }
        else if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$n身前彷彿有一道無形氣牆，但$N早已看破$n的詭計，直攻其要害。\n";
                        break;
                case 1:
                        result = HIY "$n渾若無事的接下了這一招，卻意外地受到了傷害。\n";
                        break;
                case 2:
                        result = HIY "可是$N看出了$n的金剛不壞的氣門所在，招式變幻莫測，雙手遙指$n氣門,$n心裏一慌，真氣流暢不順，露出了破綻。\n";
                        break;
                default:
                        result = HIY "只見$N這一招打了個正中！大喝一聲“破！”，結果正中$n要害。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jingang-buhuaiti", 1);
        if (lvl < 100) return 0;
        if (lvl < 150) return 50;
        if (lvl < 200) return 60;
        if (lvl < 250) return 70;
        if (lvl < 300) return 80;
        if (lvl < 350) return 90;
        if (lvl < 400) return 100;
        return 120;
}

int practice_skill(object me)
{
        if (me->query_skill("jingang-buhuaiti", 1) < 100)
                return notify_fail("你對這門護體神功的瞭解甚淺，還不足以自行鍛鍊。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練護體神功。\n");

        me->receive_damage("qi", 50);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jingang-buhuaiti/" + action;
}
