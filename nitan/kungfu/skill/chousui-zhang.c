// chousui-zhang.c 抽髓掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": ""HIB"$N臉上露出詭異的笑容，隱隱泛出綠色的雙掌掃向$n的$l"NOR"",
        "lvl"   : 0,
        "skill_name" : "抽髓掌"
]),
([        "action": ""BLU"$N突然身形旋轉起來撲向$n，雙掌飛舞著拍向$n的$l"NOR"",
        "lvl"   : 10,
        "skill_name" : "抽髓掌"
]),
([        "action": ""HIB"$N將毒質運至右手，一招「腐屍毒」陰毒無比地抓向$n的$l"NOR"",
        "lvl"   : 20,
        "skill_name" : "抽髓掌"
]),
([        "action": ""BLU"$N雙掌挾著一股腥臭之氣拍向$n的$l"NOR"",
        "lvl"   : 30,
        "skill_name" : "抽髓掌"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo)
{
        return combo == "sanyin-zhua";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技不足，無法練抽髓掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的掌法根基不足，無法練抽髓掌。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為太弱，無法練抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的抽髓掌法。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練抽髓掌。\n");
        if (me->query_skill("chousui-zhang", 1) < 50)
                me->receive_damage("qi", 45);
        else
                me->receive_damage("qi", 40);
        addn("neili", -25, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chousui-zhang", 1);
        flvl=query("jiali", me);

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl*2 + random(flvl*2),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 10) ])))
        {
                // 以下是抽髓掌的 perform sandu 中的散毒功能轉到這裡。
                if (me->query_skill("poison", 1) < 101)
                        set("body_poison", me->query_skill("poison",1)+1, me);
                if (me->query_skill("poison", 1) > 100)
                        set("body_poison", me->query_skill("poison",1)+10, me);
                //  散毒結束
                return HIW "$n" HIW "只感一陣極寒從心底升起，看來是中了$N" HIW "掌上的劇毒。\n" NOR;
        }
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
        int d_e1 = -45;
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 210;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        if (present("huo yan", environment(me)))
        {
                if( random(me->query_skill("strike"))>250 && query("neili", me)>1000 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": BLU "$N神色慘淡，伸手打開發髻，長發下垂，覆在臉上，跟著力咬舌尖，" HIR "一口鮮"
                                "血向火燄中噴去。\n那火燄忽地一暗，" HIW "隨即大為明亮，$N猛地身子急旋，如陀"
                                "螺般連轉了十多個圈子，\n" HIR "大袖拂動，整個火燄堆陡地撥起，便如一座火牆般向$n壓過去" NOR,
                                "force" : 450,
                                "dodge" : -100,
                                "parry" : -100,
                                "weapon": "火燄",
                                "damage_type": "燒傷"]);
                }
                if (random(me->query_skill("strike")) > 215 &&
                    query("neili", me)>800 )
                    {
                        addn("neili", -75, me);
                        return ([
                                "action": HIG "$N厲聲大喝，掌力加盛，綠火突然化作一個"
                                          HIR "鬥大的火球，向$n疾沖過來。\n使力極猛，去勢奇快，"
                                          HIG "只見一碧綠的火球在空中骨碌碌的迅速轉動" NOR,
                                "force" : 420,
                                "dodge" : -90,
                                "parry" : -90,
                                "weapon": "火球",
                                "damage_type": "燒傷"]);
                }
                if (random(me->query_skill("strike")) > 180 &&
                    query("neili", me)>600 )
                {
                        addn("neili", -50, me);
                        return ([
                                "action": HIR "$N衣袖一拂，一股勁氣直射入火燄之中，"+HIG+"火燄中又分出一道細細的綠火，便如一根水線般，\n"
                                          HIW "$N衣袖揮動，兩股勁風分襲$n左右" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG "綠火" NOR,
                                "damage_type": "燒傷"]);
                }
                if (random(me->query_skill("strike")) > 150 &&
                    query("neili", me)>500 )
                {
                        addn("neili", -20, me);
                        return ([
                                "action": HIR "$N隨即左掌斜拍出一道"+HIG+"綠火"+HIR+"向$n射去，聲勢洶洶，"+HIG+"便似一條綠色長蛇橫臥空際，輕輕擺動，\n"
                                          HIR "顏色又是鮮艷，"+BLU+"又是詭異，光芒閃爍不定"+HIG+"照映得$n頭臉皆碧"NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG"綠火"NOR,
                                "damage_type": "燒傷"]);
                }

                if (random(me->query_skill("strike")) > 120 &&
                        query("neili", me)>400){
                        addn("neili", -10, me);
                        return ([
                                "action": HIR "$N突然間雙眉往上一豎，右手食指點兩點，火燄堆中嗤嗤兩聲輕響，"+HIG+"爆出幾朵火花，猶如流星一般，\n"
                                          "在$N內力摧迫下，分從左右襲向$n，來勢迅速之極" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": "火花",
                                "damage_type": "燒傷"]);
                }
        }
        lvl = (int) me->query_skill("chousui-zhang", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n抽髓掌："NOR"\n");
        write(@HELP

    星宿派掌法，以腐屍毒名懾天下。
    可與三陰蜈蚣爪互備。

        學習要求：
                化功大法10級
                內力60
HELP
        );
        return 1;
}
