// animaout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int outing(object me);
int halt_outing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if( !query("animaout", me) )
                return notify_fail("你還沒有練成元嬰出世，談什麼生死玄關？\n");

        if( query("death", me) )
                return notify_fail("你已經打通生死玄關了，沒有必要再來一遍！\n");

        if( !query("no_fight", where) )
                return notify_fail("在這裡打通生死玄關？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一個能夠休息的地方閉關修行。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if( query("potential", me)-query("learned_points", me)<1000 )
                return notify_fail("你的潛能不夠，沒法閉關修行以打通生死玄關。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心閉關。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心閉關。\n");

        if( query("max_jingli", me)<2000 )
                return notify_fail("你覺得精力頗有不足，看來目前還難以"
                                   "打通生死玄關。\n");

        if( query("jingli", me)*100/query("max_jingli", me)<90 )
                return notify_fail("你現在的精力太少了，無法靜心閉關。\n");

        message_vision("$N盤膝坐下，開始冥神運功，閉關修行。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "death", me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)開始閉關修行，試圖打通生死玄關。",
                              ultrap(me) ? "大宗師" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_outing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你繼續閉關修行試圖打通生死玄關...\n" NOR);
        return 1;
}

private void stop_outing(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int outing(object me)
{
        string msg;

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "你沒有辦法繼續下去了。\n");
                message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽說%s(%s)閉關結束，似乎沒有什麼成果。",
                                      me->name(1),query("id", me)));
                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        addn("learned_points", 1, me);

        if (random(10))
                return 1;

        if( random(100000)<query("con", me) )
        {
                message_vision(HIY "只見$N" HIY "頭上現出萬朵金蓮，光"
                               "華四射，一時間麝香撲鼻、氤氳遍地！\n" NOR, me);
                tell_object(me, HIM "你覺得精力源源而生，忽然心如止水，如身出"
                            "天際，無源無盡、登時大徹大悟。\n" NOR);

                set("death", 1, me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽說%s(%s)經過閉關苦修，終"
                                      "于參悟出生死之道，打通了生死玄關。",
                                      me->name(1),query("id", me)));

                CHAR_D->setup_char(me);
                stop_outing(me);
                return 0;
        }

        switch (random(4))
        {
        case 0:
                msg = "你閉目凝神，試圖進入無我境界。\n";
                break;

        case 1:
                msg = "你試圖將元神與肢體分離，然後參悟生死之道。\n";
                break;

        case 2:
                msg = "你試圖將元神逼出七竅，然後周遊四處復又收回。\n";
                break;

        default:
                msg = "你緩緩呼吸吐納，將空氣中水露皆收為己用。\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_outing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了閉關。\n");
        message_vision(HIY "$N" HIY "輕輕嘆了一口氣，緩緩的睜開眼。\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + me->name(1) +
                              "閉關中途突然復出。");
        return 1;
}

private void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : death

當你修煉元嬰出世以後，並且具有非常高深的精力修行時，可以用
這條指令打通生死玄關。打通生死玄關後可以使你死亡後不損失經
驗和武功技能。

HELP );
        return 1;
}