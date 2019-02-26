#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("longxiang-gong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
        /*
        return force == "mizong-neigong" ||
               force == "xiaowuxiang" ||
               force == "yijinjing" ||
               force == "xixing-dafa";
        */
}

mapping *action = ({
([      "action" : "$N單掌一抖，運聚龍象般若功功力，呼嘯着向$n的$l處拍去",
        "dodge"  : 37,
        "force"  : 430,
        "attack" : 173,
        "parry"  : 41,
        "damage" : 133,
        "damage_type": "內傷"
]),
([      "action" : "$N右拳橫移，左掌運起龍象般若功的勁力，猛地拍向$n的$l",
        "dodge"  : 35,
        "force"  : 440,
        "attack" : 177,
        "parry"  : 47,
        "damage" : 121,
        "damage_type": "內傷"
]),
([      "action" : "$N吐氣揚聲，雙拳同時運滿龍象般若功功力，朝$n$l處貫去",
        "dodge"  : 37,
        "force"  : 450,
        "attack" : 182,
        "parry"  : 46,
        "damage" : 123,
        "damage_type": "內傷"
]),
([      "action" : "$N運足龍象般若功，雙拳平推，頓時一股凌厲的罡勁直襲$n",
        "dodge"  : 27,
        "force"  : 480,
        "attack" : 183,
        "parry"  : 35,
        "damage" : 145,
        "damage_type": "內傷"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("longxiang-gong", 1);

        if (lvl >= 150)
                return usage == "force" ||
                       usage == "parry" ||
                       usage == "unarmed";

        else if (lvl >= 30)
                return usage == "force";

        else
                return usage == "force";
}

int valid_learn(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if( query("str", me)<30 )
                return notify_fail("你的先天膂力孱弱，無法修煉龍象般若功。\n");

        if( query("con", me)<30 )
                return notify_fail("你的先天根骨孱弱，無法修煉龍象般若功。\n");

        if( query("gender", me) == "無性" && layer >= 1 )
                return notify_fail("你無根無性，陰陽不調，無法修煉龍象般若功。\n");

        if ((int)me->query_skill("lamaism", 1) < 100)
                return notify_fail("你對密宗心法理解不夠，難以領會龍象般若功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不足，難以領會龍象般若功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，難以領會龍象般若功。\n");

        if (me->query_skill("force", 1) < lvl)
                return notify_fail("你的基本內功水平不夠，難以修煉更深厚的龍象般若功。\n");

        if( query("max_neili", me)<layer*500 )
                return notify_fail("你的內力修為不夠，難以修煉更深厚的龍象般若功。\n");

        if (me->query_skill("lamaism", 1) < layer * 25)
                return notify_fail("你對密宗心法理解不夠，難以修煉更深厚的龍象般若功。\n");

        if (me->query_skill("unarmed", 1) < lvl && layer >= 5)
                return notify_fail("你的基本拳腳水平不夠，難以修煉更深厚的龍象般若功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if (damage_bonus < 130
           || layer < 6
            || query("neili", me)<500
            || query_temp("weapon", me )
            || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "longxiang-gong"
           || me->query_skill_mapped("unarmed") != "longxiang-gong"
           || me->query_skill_prepared("unarmed") != "longxiang-gong"
           || damage_bonus / 6 < victim->query_con() / 10
           //|| random(10) < 5
           )
                return 0;

        if (layer >= 10 && random(2) == 1)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 50) / 3, me);
                return HIY "$N" HIY "拳鋒之上竟藴藏着『" HIR "十龍十象"
                       HIY "』之力，罡勁破體，摧毀了$n" HIY "的真元！\n" NOR;
        } else
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                return HIY "$N" HIY "雙拳暗含龍象般若功第" + chinese_number(layer) +
                       "層功力，$n" HIY "心脈受震，噴出一口鮮血！\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("龍象般若功只能用學(learn)來增加熟練度。\n");
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if( lvl>400 && !query("can_perform/longxiang-gong/zhen", me) )
        {
                tell_object(me, HIR "你突然靈犀一動，領悟出數百年無人練成的真·般若極祕訣！\n" NOR);
                set("can_perform/longxiang-gong/zhen", 1, me);
        }

        if ((lvl % 30) == 0 && layer > 13)
        {
                tell_object(me, HIY "你的龍象般若功又進了一層。\n" NOR);
        } else
        if ((lvl % 30) == 0)
        {
                tell_object(me, HIY "你煉成了第" + chinese_number(layer) +
                                "層的龍象般若功。\n" NOR);
        }
}

int difficult_level()
{
        object me;
        int lvl;

        if (me = this_player())
        {
                // 有小無相功？難以學習。
                if (lvl = me->query_skill("xiaowuxiang", 1))
                        return 3000;

                // 有九陽神功？較難學習。
                if (lvl = me->query_skill("jiuyang-shengong", 1))
                        return 1000;
        }

        return 300;
}
string perform_action_file(string action)
{
        return __DIR__"longxiang-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"longxiang-gong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n龍象般若功："NOR"\n");
        write(@HELP

    “龍象般若功”，那是密宗中至高無上的護法神功。為雪山派
本門內功。【龍象般若經】言道，功成十層以上，每出一招，均具
十龍十象的大力，故名“龍象般若功”。

    “龍象般若功”共分十三層，第一層功夫十分淺易，縱是下愚
之人，只要得到傳授，一二年中即能練成。第二層比第一層加深一
倍，需時三四年。第三層又比第二層加深一倍，需時七八年。如此
成倍遞增，越是往後，越難進展。待到第五層以後，欲再練深一層，
往往便須三十年以上苦功。密宗一門，高僧奇士歷代輩出，但這一
十三層“龍象般若功”卻從未有一人練到十層以上。這功夫循序漸
進，本來絕無不能練成之理，若有人得享千歲高齡，最終必臻第十
三層境界，只是人壽有限，密宗中的高僧修士欲在天年終了之前練
到第七層、第八層，便非得躁進不可，這一來，往往陷入了欲速不
達的大危境。北宋年間，藏邊曾有一位高僧練到了第九層，繼續勇
猛精進，待練到第十層時，心魔驟起，無法自制，終於狂舞七日七
夜，自終絕脈而死。

        學習要求：
                基本內功10級
                相應的戾氣
                非出家喇嘛不能學到30級以上的龍象般若功
                太監不能學到50級以上的龍象般若功
HELP
        );
        return 1;
}
