// This program is a part of NITAN MudLIB

#include <ansi.h>

#define SLEEP_CMD       "/cmds/std/sleep"

string *msgs = ({
        HIY "$N和悅地對$n說道：“望著我的眼睛，千萬不可分神。現在你感到眼皮沉重，頭腦發暈，\n"
        "全身疲乏無力，那就閉上眼睛睡罷。”$N越說聲音越是柔和甜美。\n"
        "$n微覺不妥，要想轉頭避開$N的眼光，可是一雙眼睛竟似被$N的目光吸住了，不由自主\n"
        "的凝視著$N，竟然不知不覺的哈欠連連。\n" NOR,

        HIW "只見$N笑咪咪的凝望$n，眼中似發光芒。$n一怔，覺得曾在甚麼地方和此人會過，\n"
        "又覺得$N眼色瞧得自己極不舒服，當即轉頭避開，但過不片刻，忍不住又去望了$N一眼\n"
        "$N笑道：“下得好大的雪啊，是不是？”$n道：“是，好大的雪。”$N道：\n"
        "“來，咱們去瞧瞧雪景。”$N說話極是和悅動聽，竟有一股中人欲醉之意，$n登時 \n"
        "覺得神倦眼困，全身無力。\n" NOR,

        HIM "突然$n與$N目光相接，不禁心中微微一震，只見$N雙目中精光逼射，動人心魄。\n"
        "$N微笑道：“您累啦，您歇歇罷！”聲音柔和，極是悅耳動聽。$n果覺全身倦怠，\n"
        "心想累了這大半夜，也真該歇歇了，心念這麼一動，更是目酸口澀，精疲神困。\n" NOR,
});

string *laughMsg = ({
        HIW "$N越笑越厲害，直笑得滿地直打跌，差點閉過氣去。\n" NOR,
        HIG "$N捧住肚子，嘻嘻哈哈地直笑得兩眼翻白，喘不過氣來。\n" NOR,
        HIY "$N繼續哈哈大笑，前仰後合，似是聽到了最可笑不過的笑話。\n" NOR,
        HIM "但見$n笑得越來越歡暢，不知怎地，$N只覺全身輕飄飄的快美異常，不由自主的\n"
        "哈哈大笑起來。\n" NOR,
        HIC "$N見$n閉目良久，只道已受了自己言語所惑，昏沉睡去，正自欣喜，欲待\n"
        "再施狡計，突見$n睜開雙眼，向著自己微微而笑，便也報以微微一笑。\n" NOR,
});

private void delay(object me, object target);
private void fail(object me, object target, int times);
private void wait_kill(object me, object target);
private void start_kill(object target, object me);

void create()
{
        seteuid(getuid());
}

int exert(object me, object target)
{
        object env;

        env = environment(me);

        if( !query("can_exert/huntian-qigong/shexin", me) )
                return notify_fail("咦，你會使用懾心術嗎？\n");

        if( query("no_fight", env) || query("no_sleep_room", env )
                 || query("sleep_room", env) || query("hotel", env) )
                return notify_fail("你不可以在這裡使用懾心術。\n");

        if (! target)
                return notify_fail("你要對誰使用懾心術？\n");

        if( query("race", target) != "人類" )
                return notify_fail("你能夠催眠動物嗎？不見得吧？\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 120)
                return notify_fail("你的混天氣功修為不夠！\n");

        if (target == me)
                return notify_fail("你不能懾自己的心！\n");

        if (! wizardp(me) && wizardp(target))
        {
                message_combatd(RED "大膽！敢對巫師使用懾心術！。\n" NOR, me);
                this_player()->unconcious();
                return 1;
        }

        if( query("no_shexin", target) )
                return notify_fail("無法對此人使用懾心術。\n");

        if (! living(target))
                return notify_fail("你不能懾他的心了！\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法使用懾心術。\n");

        if (target->is_busy()) return notify_fail("此人正忙著呢！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        message_combatd(CYN "$N發出一陣陰笑。\n" NOR, me);

        me->start_busy(2);
        if( member_array(query("id", me),target->query_killer()) != -1 )
                call_out("delay", 2, me, target);
        else call_out("delay", 1, me, target);

        return 1;
}

private void delay(object me, object target)
{
        string fam;
        int myLev, tarLev, ok;

        if (! me || ! target) return;
        if (! present(target, environment(me)))
        {
                tell_object(me, "很可惜，你的目標已經不在了。\n");
                return;
        }

        if (me->is_fighting() || target->is_fighting())
        {
                tell_object(me,"戰鬥中無法使用懾心術。\n");
                return;
        }

        message_combatd( msgs[random(3)], me, target);

        myLev=(query("level", me))*(query("neili", me)/100)*(me->query_skill("force")/10);
        tarLev=query("level", target)*(query("neili", target)/100)*(target->query_skill("force")/10);

        if (myLev / 2 > tarLev) ok = 1;
        else if (tarLev / 2 >= myLev) ok = 0;
        else if (myLev / 2 + random(myLev) > tarLev) ok = 1;
        else ok = 0;

        addn("neili", -500, me);
        me->receive_damage("qi", 300);
        set("jiali", 0, me);

        if (ok == 0)
        {
                me->start_busy(15);
                call_out("fail", 1, me, target, 4);
                return;
        }
        /*
        tell_object(target, HIR "\n你只覺得昏昏欲睡，往地下角落一躺，開始睡覺。\n" NOR);
        tell_object(target, HIR "不一會兒，你就進入了夢鄉。\n" NOR);
        tell_object(me,"\n"HIY+query("name", target)+"往地下角落屈身一躺，不一會便鼾聲大作，做起夢來。\n"NOR);
        */

        me->start_busy(1);
        set_temp("block_msg/all", 1, me);

        fam=query("family/family_name", target);
        if( fam != "丐幫") set("family/family_name", "丐幫", target);

        SLEEP_CMD->main(target);

        if( fam != "丐幫") set("family/family_name", fam, target);

        delete_temp("block_msg/all", me);
        return;

}

private void fail(object me, object target, int times)
{
        if (times != -1)
        {
                message_combatd( "\n" + laughMsg[times], me, target);
                call_out("fail", 2, me, target, times-1);
        }

        else
        {
                message_combatd( HIR "\n$N笑得忽然閉了氣。\n" NOR, me);
                me->unconcious();

                if (! userp(target)) call_out("wait_kill", 3, me, target);
                return;
        }
}

private void wait_kill(object me, object target)
{
        if (! target || ! living(target)) return;
        if (environment(me) != environment(target))
        {
                return;
        }

        if (! living(me)) call_out("wait_kill", 2, me,  target);

        else
        {
                message_combatd(HIR "$N對著$n哼了一聲：“" +
                                RANK_D->query_self_rude(target)+
                                "明人不做暗事，現在你醒了，拿命來！！”\n"NOR, target, me);
                call_out("start_kill", 0, target, me);
        }
        return;
}

private void start_kill(object target, object me)
{
        me->want_kill(target);
        target->kill_ob(me);
        me->fight_ob(target);
        return;
}
