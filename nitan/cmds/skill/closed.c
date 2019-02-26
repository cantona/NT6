// closed.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      100

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if (! ultrap(me))
                return notify_fail("你還沒有到大宗師的境界，還是好好學習鍛鍊吧。\n");

        if (wizardp(me))
                return notify_fail("巫師閉什麼關？\n");

        if( !query("no_fight", where) )
                return notify_fail("在這裏閉關？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一個能夠休息的地方閉關。\n");

        if( where->is_chat_room() )
                return notify_fail("在這裏閉關？不太安全吧？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( query("potential", me)-query("learned_points", me)<10000 )
                return notify_fail("你的潛能不夠，沒法閉關修行。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心閉關。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心閉關。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你覺得內力頗有不足，看來目前還難以"
                                   "進行長時間的閉關修煉。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了，無法靜心閉關。\n");

        message_vision("$N盤膝坐下，開始冥神運功，閉關修行。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "closed", me);
        CLOSE_D->user_closed(me, "closed");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("大宗師%s(%s)開始閉關修行。",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_closing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你繼續閉關...\n" NOR);
        return 1;
}

int filter_skill(string sk, object me)
{
        if (me->query_skill(sk, 1) < 200 || ! me->can_improve_skill(sk))
                return 0;

        if (SKILL_D(sk)->type() != "martial")
                return 0;

        if (SKILL_D(sk)->valid_enable("force"))
                return 1;

        if (SKILL_D(sk)->valid_enable("parry") ||
            SKILL_D(sk)->valid_enable("dodge"))
                return 0;

        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot;
        int r, period;
        int exp_inc;
        string *ks;

#ifdef DB_SAVE
        if (! interactive(me) &&
            !MEMBER_D->is_valid_member(query("id", me)) && 
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        pot=query("potential", me);
        if( pot <= query("learned_points", me) )
        {
                tell_object(me, "你的潛能耗盡了。\n");
                message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽説%s(%s)閉關功德圓滿。",
                                      me->name(1),query("id", me)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        t=query_temp("last_closing", me);
        tn = time();
        if (tn - t < 0)
        {
                set_temp("last_closing", tn, me);
                return 1;
        }

        period = PERIOD;
        if (present("closed charm", me))
                period /= 4;
                
#ifdef DB_SAVE
        if (me->is_vip())             
                period /= 2;
#endif

        if (tn - t < period)
                return 1;

        set_temp("last_closing", tn, me);
        if( me->add("learned_points",PERIOD_POT/2+random(PERIOD_POT))>pot )
                set("learned_points", pot, me);

        if (random(10) == 0)
                tell_object(me, "閉關修煉中...\n");

        if ((random(100) < 3) && me->can_improve_neili())
        {
                tell_object(me, HIR "你對內功有所領悟，感到內力進步了！\n" NOR);
                addn("improve/neili", 1, me);
                me->improve_neili(10 + random(20));
        }

        if ((random(100) < 3) && me->can_improve_jingli())
        {
                tell_object(me, HIM "你對神通有所領悟，感到精力進步了！\n" NOR);
                addn("improve/jingli", 1, me);
                me->improve_jingli(5 + random(10));
        }

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc=exp_inc*(100+query("int", me))/100;
        addn("combat_exp", exp_inc, me);
        me->improve_skill("martial-cognize", 800 + random(800));

        ks = filter_array(keys(me->query_skills()), (: filter_skill :), me);
        if (r = sizeof(ks))
        {
                r = random(r);
                tell_object(me, HIY "你對" + to_chinese(ks[r]) + "有所感悟。\n" NOR);
                me->improve_skill(ks[r], 5000 + random(1000));
        }

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了閉關。\n");
        message_vision(HIY "$N" HIY "大喝一聲，睜開眼來，一股氣流登時"
                       "將眾人迫退四步。\n\n" NOR, me);
        // addn("potential", (query("learned_points", me) - query("potential", me)) / 2);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + me->name(1) +
                              "閉關中途突然復出。");
        return 1;
}

protected void user_quit(object me)
{
        if (! objectp(me) || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : closed

閉關修行，只有你到了大宗師的境界以後才能夠閉關修行。要求必須在
一個安全並且可以休息的地方才能閉關，閉關前需要有一萬點潛能，閉
關開始以後，玩家離線以後其角色將仍然在線修行，直到玩家中止閉關
(halt)或是潛能耗盡。期間內玩家的經驗、技能、內力將會提升。

HELP );
        return 1;
}
