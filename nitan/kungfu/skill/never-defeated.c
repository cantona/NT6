// never-defeated.c 不敗神功

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        "$n移開數步，恰好躲過了$N的攻擊。\n",
        "$n忽然反擊，直指$N的破綻，逼得$N只能回守。\n",
        "$n輕身閃避，將$N的實招全部躲過。\n",
        "$n腳下一個蹌踉，似乎無意，卻剛好躲過$N這一擊。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("never-defeated", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *action_default = ({
([      "action" : "$N攻勢忽緩而不疏，似劍法又似刀法，捉摸不定向$n慢慢推去",
        "force" : 410,
        "attack": 150,
        "dodge" : 70,
        "parry" : 120,
        "damage": 225,
        "damage_type":  "震傷"
]),
([      "action":"$N手中的$w突煥氣象森嚴，便似千軍萬馬奔馳而來，橫掃$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 85,
        "parry" : 110,
        "damage": 210,
        "damage_type":  "擦傷"
]),
([      "action":"$N舉起手中的$w，對著$n亂砍亂砸，沒有半點章法",
        "force" : 430,
        "attack": 170,
        "dodge" : 70,
        "parry" : 130,
        "damage": 205,
        "damage_type":  "割傷"
]),
([      "action":"$N運用$w幻化做一個一個圓圈，似乎要將$n包圍",
        "force" : 425,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type":  "內傷"
]),
([      "action":"$N含笑回轉$w，伸手一指，頗得拈花指之意，點向$n的$l",
        "force" : 530,
        "attack": 176,
        "dodge" : 75,
        "parry" : 115,
        "damage": 200,
        "damage_type":  "刺傷"
]),
([      "action":"$N長嘆一聲，將$w隨手遞出，連自己也不知道也攻向哪裡",
        "force" : 440,
        "attack": 170,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "割傷"
]),
([      "action":"$N神色凝重，$w上劈下切左右橫掃，挾雷霆萬鈞之勢逼往$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 95,
        "parry" : 120,
        "damage": 220,
        "damage_type":  "內傷"
]),
([      "action":"$N運起$w，就如狂風暴雨，霍霍亮光中反攻$n的$l，嘗試逼$n自守",
        "force" : 420,
        "attack": 150,
        "dodge" : 95,
        "parry" : 135,
        "damage": 200,
        "damage_type":  "內傷"
]),
([      "action":"$N突然如痴如狂，手中的$w猛然向$n周身亂刺亂削",
        "force" : 410,
        "attack": 165,
        "dodge" : 85,
        "parry" : 125,
        "damage": 235,
        "damage_type":  "割傷"
]),
([      "action":"$N將$w隨手一擺，$n反而自己向$w撞將上來，神兵之威，實人所難測",
        "force" : 430,
        "attack": 180,
        "dodge" : 75,
        "parry" : 110,
        "damage": 225,
        "damage_type":  "瘀傷"
]),
([      "action":"$N手中的$w忽起劍勢，卻似或刀法，又夾雜棍杖之意，令$n眩目",
        "force" : 420,
        "attack": 175,
        "dodge" : 85,
        "parry" : 130,
        "damage": 220,
        "damage_type":  "刺傷"
]),
});

mapping *action_whip = ({
([      "action" : "$N攻勢忽緩而不疏，$w變化無常，捉摸不定向$n慢慢卷去",
        "force" : 430,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "擦傷"
]),
([      "action":"$N手中的$w突煥氣象森嚴，便似千軍萬馬奔馳而來，$w就如棍棒一般橫掃$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "擦傷"
]),
([      "action":"$N卷起手中的$w，就如鐵錘一般對著$n亂砍亂砸，沒有半點章法",
        "force" : 440,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "割傷"
]),
([      "action":"$N運用$w幻化做一個一個圓圈，似乎要將$n團團包圍",
        "force" : 425,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "內傷"
]),
([      "action":"$N含笑回轉$w，伸手一指，頗得拈花指之意，點向$n的$l",
        "force" : 510,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 200,
        "damage_type": "刺傷"
]),
});

string *usage_skills = ({ "sword", "blade", "dagger",
                          "staff", "hammer", "club", "whip",
                          "dodge", "parry", "force", "throwing" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "never-defeated";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        switch(weapon?query("skill_type", weapon):"default" )
        {
        case "whip":
                return action_whip[random(sizeof(action_whip))];
        default:
                return action_default[random(sizeof(action_default))];
        }
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("combat_exp", me)<3000000 )
                return notify_fail("你覺得不敗神功深奧之極，"
                                   "憑自己的戰鬥經驗一時間難以領會。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你覺得不敗神功過于深奧，以"
                                   "自己的武學修養全然無法明白。\n");

        if( query("character", me) != "狡黠多變" && 
            query("character", me) != "國士無雙" )
                return notify_fail("你學了半天，發現不敗神功古怪的"
                                   "緊，不合常理，根本無法領會。");

        if( query("int", me)<22 )
                return notify_fail("你覺得不敗神功過于深奧，絕"
                                   "非自己的智力所能理解。\n");

        if( query("gender", me) == "無性" && 
            (int)me->query_skill("never-defeated", 1) > 239)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的不敗神功。\n");

        level = me->query_skill("never-defeated", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你覺得自己的武學修養有限，難以領會更高深的不敗神功。\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("你對基本內功的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("你對基本招架的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("dodge", 1) < level)
                return notify_fail("你對基本輕功的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("sword", 1) < level)
                return notify_fail("你對基本劍法的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("blade", 1) < level)
                return notify_fail("你對基本刀法的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("whip", 1) < level)
                return notify_fail("你對基本鞭法的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        if (me->query_skill("throwing", 1) < level)
                return notify_fail("你對基本暗器的理解還不夠，無法繼續"
                                   "領會更高深的不敗神功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("不敗神功博大精深，無法簡單的通過練習進步。\n");
}

int difficult_level()
{
        return 500;
}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int)me->query_skill("never-defeated", 1) < 200
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me)
        ||  me->query_skill_mapped("parry") != "never-defeated")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("parry", 1) / 2 +
        me->query_skill("never-defeated", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "毫不理會$N的攻勢，劍意無窮，以攻為守。"
                                            "$N攻勢被破，大感驚訝，頓時破綻百出。\n"
                                            "$n劍鋒一指，劍招源源而出，對著$N反攻數劍！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "舉劍反攻，後發先至地刺向$N，不僅把"
                                            "$N招術封死，更刺向$N的破綻之處！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "提劍回刺，落點正是$N的破綻，"
                                            "$N不得不撤招嚴守，身形一晃間已退出丈許！\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "卻見$n" HIC "箭步向前，劍式直指$P" HIC
                                            "虎口，招式迅捷無比，使得$N" HIC "閃身而退"
                                            "。\n" NOR]);
                        break;
                case 4:
                        result += (["msg" : HIC "$n" HIC "突然一劍點向$N" HIC "，雖一劍"
                                            "卻暗藏無數後著，$N" HIC "頓時手足無措，攻"
                                            "勢不由自主停了下來。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "眼見避無可避，盡然力求同歸于盡，劍氣疾刺$N雙眼，"
                                            "居然出乎意料地將$N的攻擊止住。\n" NOR]);
                        break;
                }

                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() +
                                 HIY "，中攻直進一劍挺進，可是$N" HIY "反招更快"
                                 "，進襲$n" HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + "輕挑"
                                 "，" HIY "正指向$N" HIY "攻勢中的破綻，可是$N"
                                 HIY "身形一變，破綻立刻不成為破綻。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY
                                 "續變換數種劍招，然而$N" HIY "理也不理，再次攻"
                                 "出，絲毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
            || query("neili", me)<200
           || me->query_skill("never-defeated", 1) < 250)
                return 0;


        if (damage_bonus / 2 > victim->query_dex())
        {
                addn("neili", -100, me);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                addn("neili", -((damage_bonus-random(80))/2), victim);

                return HIR "緊接著$N" HIR "隨心所欲一招襲向$n" HIR "，$n" HIR "根本無法抵擋，立受重傷，鮮血狂吐！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"never-defeated/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"never-defeated/exert/" + action;
}

