// yijinjing.c 少林 易筋經神功

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("yijinjing", 1);
        return (lvl / 20) * (lvl / 10) * 25 * 15 /100;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("con", me)<20 )
                return notify_fail("你研究了一會兒，只覺得眼前金星亂冒，太陽穴突突的跳。\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不夠，無法學習易筋經神功！\n");

        /*
        if (me->query_skill("freezing-force", 1))
                return notify_fail("你已經將易筋經神功和冰蠶寒毒合煉成了一門新內功了。\n");
        */

        if (me->query_skill("force", 1) < me->query_skill("yijinjing", 1))
                return notify_fail("你的基本內功水平不夠，難以領悟更高深的易筋經神功！\n");

        if( query("gender", me) != "男性" )
                return notify_fail("你不是男性，無法練習易筋經神功。\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("易筋經神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}
/*
void skill_improved(object me)
{
        int skill, lit;

        skill = me->query_skill("yijinjing", 1);
        lit = me->query_skill("literate", 1);

        if( skill == 200 && !query("sl/yijinjing", me) )
        {
                tell_object(me, HIW "\n忽然，你感道體內內息奔走，越轉越快，瞬時間已經在全身上下運行了一周天，復匯聚于丹田之中！\n" NOR);
                addn("max_neili", random(lit+skill), me);

                if( query("max_neili", me)>me->query_neili_limit() )
                        set("max_neili", me->query_neili_limit(), me);

                set("sl/yijinjing", 1, me);
        }
        if (skill == 400)
        {
                tell_object(me, HIW "\n忽然，你感道體內內息奔走，越轉越快，瞬時間已經在全身上下運行了十周天，復匯聚于丹田之中！\n" NOR);
                tell_object(me, HIW "你修煉成百毒不侵神功了。\n" NOR);
                set_temp("nopoison", 1, me);
        }
}
*/

string *fanzhen_msg = ({
        "只震得$N胸內腹中，有如五臟一齊翻轉！\n",
        "搶先反震，將$N震得臉如白紙，全無血色！\n",
        "震得$N心肺欲裂，騰騰騰連退數步！\n",
        "功力已布滿全身，將$N的力量反震回去！\n",
        "震得$N天旋地轉，騰騰騰連退七八步！\n",
        "和$N一撞，只震的$p胸口氣血翻湧！\n",
        "$N便如撞在一堵棉花作面，鋼鐵為裡的厚牆上一般，震退數步！\n",
        "$N剛碰到$p，突然身子一震，登時飛了出去！\n",
});
/*
mixed valid_damage(object me,object victim,int damage_bonus,int factor)

//factor= 加力 damage_bonus=臂力 .
{
        int ap,dp;
//內功相差太多(至少2倍以上),內力傷害全部抵消,基本上不出現
        ap=me->query_skill("force");
        dp=victim->query_skill("force");
        if( random(ap/2)>dp && query("neili", me)>2000 )
        {

                if (random(10)==1) tell_object(victim, "你只覺得如同擊在金屬上，頭腦裡閃過一個念頭：金屬罩！\n");
                else tell_object(victim,HIY"你只覺得勁力如同擊在金屬罩，根本無法傷他分毫！\n"NOR);
                tell_object(me, HIY"你只覺得勁力襲體，急忙運起金鐘罩神功，一股真氣彌漫全身！\n"NOR);
                addn("neili", -2*damage_bonus, me);
                return -damage_bonus;
        }
        else if( (random(ap*2)>dp) && query("neili", me)>1500 )
        {
                if (random(10)==1) tell_object(victim,HIY"你只覺得如同擊在金屬上，頭腦裡閃過一個念頭：“金屬罩”！\n"NOR);
                else tell_object(victim,HIY"你只覺得勁力如同擊在金屬上，虎口隱隱作痛！\n"NOR);
                tell_object(me, HIY"你只覺得勁力襲體，勉力運起金鐘罩，一股真氣彌漫全身！\n"NOR);
                addn("neili", -damage_bonus, me);
                return -random(damage_bonus);
        }
        return 0;
}
*/
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;

        if( query("family/family_name", me) != "少林派" )
                return;

        if ((int) me->query_skill("yijinjing", 1) < 200 ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);

                        msg = random(2) ? HIR "$n身上生出一股反震之力，" : HIR "$n身上金剛不壞體神功隨心而起，";

                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;

                        ob->receive_damage("qi", damage / 10, me);
                        ob->receive_wound("qi", damage / 20, me);

                        result += ([ "msg" : msg ]);

                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                                result += ([ "msg" : HIR "好似有一堵無形的牆在$n面前阻擋著，結果"
                                                     "$N" HIR "一下子被反彈，震得$N"
                                                     HIR "手臂發麻！\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "結果$n身上生出一股反震之力，$N只覺虎口一熱，" +
                                                     weapon1->name() + HIR "頓時脫手而出，飛出丈外！\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int skill;
        int i,j;

        if( query("family/family_name", me) != "少林派" )
                return;

        if (me->query_skill("yijinjing", 1) < 400 ||
            me->is_busy())
                return;

        skill = me->query_skill("force");

        i = damage_bonus * (skill + 1) / 1000;
        i = i/2+ random(i);
        if( query_temp("weapon", me) )
                i = i*3;
        if( query_temp("apply/damage", me) >= 1000 )
                i = i/3;

        j = me->query_skill("yijinjing", 1) / 2;
        i += j;
        message_combatd(HIR"$N"+HIR+"高喧一聲佛號，將體內九陽真氣聚于雙臂，狹雷霆之勢攻向$n！\n" NOR, me,victim);

        return i;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

string query_description()
{
        return
        "易筋經乃少林寺頭等絕技，由內及外，為無上伏魔神功。此內功是少林鎮寺"
        "之寶，毅力一般者無法學成，其三階段分別為：0-200，200-400，>400。初"
        "級易筋經可強身健體，提高修為；中級可降妖伏魔，成金剛之體；高級可砍"
        "妖除魔于無形，御力修身，百毒不侵。";
}

int help(object me)
{
        write(HIC"\n易筋經神功："NOR"\n");
        write(@HELP

    《易筋》，《洗髓》二經向為少林鎮寺之寶，相傳為達摩祖師
所創，載有不少天竺高僧的瑜伽秘術，但由于其習練艱難，須得勘
破“我相，人相”，心中不存修習武功之念，故歷代弟子罕有練成
者。
    《洗髓》記載天下所有武功的精要，《易筋》則是一門極其高
深的內功心法書籍。

        學習要求：
                未破色戒的童男之身
                未犯戒
                混元一氣功100級
                相應級別的禪宗心法
HELP
        );
        return 1;
}
