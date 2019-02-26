// This program is a part of NT MudLIB
// qiankun-danuoyi.c 乾坤大挪移

#include <ansi.h>;
#include <combat.h>

inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "parry"; }

string main_skill() { return "yinyang-shiertian"; }

string *parry_msg = ({
        HIY"$N一招擊在$n身上，卻被$n暗運乾坤大挪移，將內力盡數移入地下。\n"NOR,
        HIW"$n輕輕一帶，$N發現自己招數回擊過來，嚇得往後倒退幾步。\n"NOR,
        HIC"$n手臂迴轉，在$N手肘下輕輕一推，$N招數落空。\n"NOR,
        HIG"$n右手伸出，在$N手腕上輕輕一拉，$N收勢不住，直往前撲去。\n"NOR,
        MAG"$n身形不動，$N一招擊下，有如石沉大海，不覺呆住了。\n"NOR,
        HIM"$n左牽右引，$N如身處漩流，連續轉了好幾個圈。\n"NOR,
        GRN"$n雙手迴圈，$N只覺得前面好像有一堵牆，再也攻不進去。\n"NOR,
        HIY"$n輕輕一轉，$N一招擊在地上，只打得塵土飛揚。\n"NOR,
});
mapping *action = ({
([      "action": "$n輕輕一轉，一招擊在地上，只打得塵土飛揚。",
        "force" : 350,
        "attack": 90,
        "dodge" : -90,
        "parry" : -90,
        "damage": 100,
        "damage_type":  "刺傷"
]),
});
string *pfail_msg = ({
        "$n暗運乾坤大挪移，試圖將內力盡數移入地下，然而$N早已勘破其中奧妙，內力變化莫測。\n",
        "$n輕輕一帶，$N發現自己招數回擊過來，急忙變招，身轉如意，反讓$n防不勝防。\n",
        "$n手臂迴轉，在$N手肘下輕輕一推，然而$N招數忽的一變，並未落空。\n",
        "$n右手伸出，在$N手腕上輕輕一拉，$N收勢不住，順勢變招撲前直擊。\n",
        "$n左牽右引，$N如身處漩流，順勢變招，圓轉如意，隨心所欲。\n",
        "$n雙手迴圈，$N只覺得前面好像有一堵牆，猛然警醒，聚力於一點，力攻對方。\n",
});
string *dodge_msg = ({
        "$N一招擊在$n身上，卻被$n暗運乾坤大挪移，將內力盡數移入地下。\n",
        "$n輕輕一帶，$N發現自己招數回擊過來，嚇得往後倒退幾步。\n",
        "$n手臂迴轉，在$N手肘下輕輕一推，$N招數落空。\n",
        "$n右手伸出，在$N手腕上輕輕一拉，$N收勢不住，直往前撲去。\n",
        "$n身形不動，$N一招擊下，有如石沉大海，不覺呆住了。\n",
        "$n左牽右引，$N如身處漩流，連續轉了好幾個圈。\n",
        "$n雙手迴圈，$N只覺得前面好像有一堵牆，再也攻不進去。\n",
        "$n輕輕一轉，$N一招擊在地上，只打得塵土飛揚。\n",
});

int valid_enable(string usage)
{
        return (usage == "parry") /*|| (usage == "dodge") || (usage=="move")*/;
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_research(object me)
{
        int canlvl;
        canlvl = ((int)query("int", me) - 30 ) * 50;

        if (query("int", me) < 34 &&
                me->query_skill("qiankun-danuoyi", 1) >= canlvl )
                return notify_fail(HIG "你覺得更深層次的乾坤大挪移實在是深奧無比，全然無法理解。\n" NOR);

        if (me->query_skill("qiankun-danuoyi", 1) < 310)
                return notify_fail(HIG "你對乾坤大挪移的認識還不足以自行研究提高！\n" NOR);

        return 1;
}

int valid_learn(object me)
{
        int layer;

        if( (!me->query_family() ||
            me->query_family() != "明教") && (!query("reborn/times", me) || member_array("明教", query("reborn/fams", me)) == -1) )
                return notify_fail("你不是明教中人，無法修習！\n");

        if (query("gender", me) == "無性" &&
            me->query_skill("qiankun-danuoyi", 1) >= 50)
                return notify_fail("你試圖按照心法修煉大挪移，卻"
                                   "覺得心中一陣迷茫，難以繼續。\n");

        if (me->query_condition("qiankun-except"))
                return notify_fail("你現在體內若冰、四肢皆寒、面赤"
                                   "如火，無法繼續修煉神功。\n");

        layer = (int)me->query_skill("qiankun-danuoyi", 1) / 50;
        if (layer > 7) layer = 7;

        if (query("int", me) < 27 + layer)
                return notify_fail("你覺得第" + chinese_number(layer) +
                                   "層乾坤大挪移實在是深奧無比，全然無法理解。\n");

        if ((int)query("max_neili", me) < 6000)
                return notify_fail("你的內力修為太差，無法修煉乾坤大挪移。\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的內功火候不夠，無法修煉乾坤大挪移。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本招架火候有限，無法體會更高深的乾坤大挪移。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本內功火候有限，無法體會更高深的乾坤大挪移。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        mapping sk, ma;
        int ap, dp, mp;
        string wn, na;

        sk = ob->query_skills();
        ma = ob->query_skill_map();

        if ((int)me->query_skill("qiankun-danuoyi", 1) < 100
           || ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("parry", 1);

        // 挪移乾坤效果
        if (query_temp("nuozhuan", me))
        {
                me->stop_busy();
                me->clear_weak();
        }

        if (ap / 3 + random(ap) < dp
        &&  !me->is_busy()
        &&  !query_temp("nuoyi", me)
        &&  !query_temp("nuoyi", ob)
        &&  me->query_skill("qiankun-danuoyi", 1) > 350
        &&  query("max_neili", me) > random(query("max_neili", ob))
        &&  sizeof(sk)
        &&  sizeof(ma) != 0
        &&  mapp(ma))
        {
                if (objectp(weapon = query_temp("weapon", ob)))
                {
                        wn = query("skill_type", weapon);
                        na = ob->query_skill_mapped(wn);
                } else

                if (ob->query_skill_prepared("finger"))
                        na = ob->query_skill_mapped("finger");
                else

                if (ob->query_skill_prepared("strike"))
                        na = ob->query_skill_mapped("strike");
                else

                if (ob->query_skill_prepared("claw"))
                        na = ob->query_skill_mapped("claw");
                else

                if (ob->query_skill_prepared("cuff"))
                        na = ob->query_skill_mapped("cuff");
                else

                if (ob->query_skill_prepared("hand"))
                        na = ob->query_skill_mapped("hand");
                else
                        na = ob->query_skill_mapped("unarmed");

                msg = HIM "\n$N" HIM "一招攻出，卻見$n" HIM "迎身而"
                      "上，冷笑道：「區區" + CHINESE_D->chinese(na) +
                      HIM "，能奈我何？」\n$n" HIM "當即運起乾坤大挪"
                      "移第七層心法，企圖挪移$N" HIM "的攻勢。\n\n" NOR;

                me->start_call_out((: call_other, __FILE__, "nuoyi",
                                      ob, me, damage :), 1);
                set("nuoyi/"+query("id", ob), 1, me);
                // me->start_busy(2);

                result = ([ "damage" : -damage,
                            "msg"    : msg ]);

                return result;
        } else
        if (ap / 3 + random(ap) < dp || (query_temp("nuozhuan", me) && random(100) < 90))
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = pfail_msg[random(sizeof(pfail_msg))];
                msg = replace_string(msg, "$N", "$N" HIY);
                msg = replace_string(msg, "$n", "$n" HIY);
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        layer = lvl / 50;
        if (layer > 7) layer = 7;

        if (! layer)
        {
                tell_object(me, HIM "你潛心修煉乾坤大挪"
                            "移心法，若有所悟。\n" NOR);
        } else
        if ((lvl % 50) == 0)
        {
                tell_object(me, HIM "你修煉成了第" + chinese_number(layer) +
                            "層的乾坤大挪移心法。\n" NOR);
        } else
                tell_object(me, HIM "你對第" + chinese_number(layer) +
                            "層的乾坤大挪移心法又加深了一層瞭解。\n" NOR);

        if( query("special_skill/nopoison", me) ) return;
        if (lvl > me->query_skill("force") * 2 / 3)
        {
                if (lvl < me->query_skill("force") * 2 / 3 + 10)
                {
                        tell_object(me, HIG "你覺得內息一陣紊亂，丹田時冷時"
                                        "熱，不由得大吃一驚。\n心想莫非是走"
                                        "火入魔？丹田越來越是寒冷，極為難受"
                                        "。\n" NOR);

                        message("vision", HIG + me->name() + HIG "的臉色忽紅"
                                          "忽綠，變得不停，只是渾身顫抖，似"
                                          "乎十分痛苦。\n" NOR,
                                          environment(me), ({ me }));
                        return;
                }
                tell_object(me, HIB "你忽然覺得丹田騰起一陣寒意，霎時間四肢"
                                "百賅一起變得寒冷無比，忍不住大聲呻吟。\n" NOR);

                message("vision", HIB + me->name() + HIB "忽然一抖，臉色忽然"
                                  "變得慘白，隱然籠罩了一股綠氣，呻吟不止。"
                                  "\n" NOR, environment(me), ({ me }));
        } else

        if (lvl < 350 && (lvl * 20 + 4000) > query("max_neili", me))
        {
                if ((lvl * 20 + 4000) < query("max_neili", me) + 200)
                {
                        tell_object(me, HIR "你試着運轉了一下內息，一時覺得內"
                              "力不濟，看來還是不要貿然修煉大挪移神功。\n" NOR);
                        return;
                }

                tell_object(me, HIR "你試着運轉了一下內息，忽然覺得一口氣"
                      "竟然轉不過來，頓時心中絞痛，接連吐了幾口鮮血。\n" NOR);
                message("vision", HIR + me->name() + HIR "臉色忽然"
                        "一變，嘔出幾口鮮血，觸目驚心。\n" NOR,
                        environment(me), ({ me }));
        } else
                return;

        me->apply_condition("qiankun-except", lvl +
           (int)me->query_condition("qiankun-except"));
}

void nuoyi(object ob, object me, int damage)
{
        string msg;
        int ap, dp;

        if (! ob
           || ! living(me)
           || ! me->is_fighting(ob)
           || ! query_temp("nuoyi/" + query("id", ob), me))
                return;

        msg = HIM "\n$N" HIM "乾坤大挪移第七層心法施展出來，頓將先前所積蓄"
              "的十餘道力量歸併為一掌，朝$n" HIM "疾拍而出，這便如一座大湖"
              "在山洪爆發時儲滿了洪水卻突然崩決，洪水急衝而出一般。\n" NOR;

        ap = me->query_skill("parry");
        dp = ob->query_skill("force");

        // me->start_busy(2);

        if (dp / 2 + random(dp) < ap)
        {
                msg += COMBAT_D->do_damage(me, ob, SPECIAL_ATTACK, damage, 600,
                                           HIR "只聽$n" HIR "一聲慘叫，將$N"
                                           HIR "返回的力道受了個十足，全身喀"
                                           "嚓喀嚓一陣脆響，腕骨、臂骨、肩骨"
                                           "、肋骨竟然一齊折斷。\n" NOR);
        } else
        {
                msg += HIC "$n" HIC "眼見$P來勢洶湧，不敢"
                       "大意，施出渾身解數化解開來。\n" NOR;
        }
        delete_temp("nuoyi", me);
        message_sort(msg, me, ob);
}

int practice_skill(object me)
{
        return notify_fail("乾坤大挪移只能通過讀<<乾坤大挪移心法>>提高。\n");
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        if (lvl < 50) return 50;
        if (lvl < 100) return 80;
        if (lvl < 150) return 100;
        if (lvl < 200) return 120;
        if (lvl < 250) return 130;
        if (lvl < 300) return 140;
        if (lvl < 350) return 150;
        if (lvl < 400) return 200;
        return 220;
}

string perform_action_file(string action)
{
        return __DIR__"qiankun-danuoyi/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.5; }

int help(object me)
{
        write(HIC"\n乾坤大挪移："NOR"\n");
        write(@HELP

    “乾坤大挪移”是明教歷代相傳一門最厲害的武功，是明教的
護教神功。為波斯大盜山中老人所創，專門講述運氣使力的法門。
中原會用的人甚少，自明教三十三代教主陽頂天死後，幾乎失傳，
但後來張無忌一番奇遇，以其深厚的內功一朝而成。乾坤大挪移只
作招架和輕功用，不具攻擊。其威力之所在是可以把別人的招數盡
數還於對方。
    乾坤大挪移神功的主旨，乃在顛倒一剛一柔、一陰一陽的乾坤
二氣，臉上現出青紅之色，便是體內血液沉降、真氣變換之象。練
至第六層時，全身都能忽紅忽青，但到第七層時，陰陽二氣轉換於
不知不覺之間，外形上便半點也瞧不出表徵了。其根本道理也並不
如何奧妙，只不過先求激發自身潛力，然後牽引挪移敵勁，但其中
變化神奇，卻是匪夷所思。

        學習要求：
                基本內功100級並不得低於乾坤大挪移的級別
                九陽神功不得低於乾坤大挪移的級別
                內力1500並不得低於乾坤大挪移的級別的15倍
                太監無法領悟100級以上的乾坤大挪移
HELP
        );
        return 1;
}
