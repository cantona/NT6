// sleep.c
// Updated by Lonely

#include <ansi.h>
#include <command.h>

void wakeup(object me);

int main(object me, string arg)
{
        object obj, old_target;
        int i;
        object *inv;
        mapping fam;
        mapping cnd;
        string *kc;
        object where = environment(me);
        object bag;
        int qi, jing;

        seteuid(getuid());

        if (! where) return 1;

        if( (!(fam=query("family", me)) || fam["family_name"] != "丐幫" )
              && !(query("sleep_room", where) )
             && !objectp(bag = present("sleepbag", me))
              || (query("no_sleep_room", where)) )
             return notify_fail("這裡不是你能睡的地方！\n");


        if (me->is_busy())
                return notify_fail("你正忙著呢！\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中不能睡覺！\n");

        if( query("hotel", where) && !(query_temp("rent_paid", me)) )
        {
                message_vision("店小二從門外對$N大叫：把這裡"
                               "當避難所啊！先到一樓付錢後再來睡！\n",me);
                return 1;
        }

        jing=query("jing", me);
        qi=query("qi", me);
        if (jing < 0 || qi < 0)
                return notify_fail("你現在接近昏迷，睡不著覺。\n");
        cnd = me->query_condition();
        if (cnd && sizeof(cnd))
        {
                kc   = keys(cnd);
                for (i = 0; i < sizeof(kc); i++)
                {
                        if (CONDITION_D(kc[i])->min_qi_needed(me) > qi ||
                            CONDITION_D(kc[i])->min_jing_needed(me) > jing)
                        {
                                message("vision", me->name() + "看樣子是想睡覺，"
                                        "可是輾轉反側，就是睡不著。\n",
                                        environment(me), me);
                                tell_object(me, "你想合上眼睛好好睡上一覺，可是" +
                                            to_chinese(kc[i]) + "不斷折磨著你，"
                                            "讓你輾轉難眠。\n");
                                return 1;
                        }
                }
        }

        if( query("sleep_room", where) )
        {
            write("你往床上一躺，開始睡覺。\n");
            write("不一會兒，你就進入了夢鄉。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N一歪身，倒在床上，不一會"
                           "便鼾聲大作，進入了夢鄉。\n",me);
        } else
        if (objectp(bag = present("sleepbag", me)))
        {
                write("你展開一個睡袋，鑽了進去，開始睡。\n");
            write("不一會兒，你就進入了夢鄉。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N展開一個睡袋，鑽了進去，不一會就進入了夢鄉！\n",me); 
        } else
        {
            write("你往地下角落一躺，開始睡覺。\n");
            write("不一會兒，你就進入了夢鄉。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N往地下角落屈身一躺，不一"
                           "會便鼾聲大作，做起夢來。\n",me);
        }

        set("no_get", 1, me);
        set("no_get_from", 1, me);

        set_temp("sleeped", 1, me);
        if( query("hotel", where) )
            delete_temp("rent_paid", me);

        me->disable_player(" <睡夢中>");
        me->start_call_out(bind((: call_other, __FILE__, "wakeup", me :), me),
                           3 + random(120/me->query_con()));

        return 1;
}

void wakeup(object me)
{
        if( !me || !query_temp("sleeped", me) )
                return;

        if (living(me))
        {
                delete_temp("sleeped", me);
                return;
        }

        me->enable_player();
        set_temp("block_msg/all", 0, me);
        delete("no_get", me);
        delete("no_get_from", me);
        delete_temp("sleeped", me);

        // if (time() - me->query("last_sleep") >= 30)
        if (time())
        {
                set("qi",query("eff_qi",  me), me);
                set("jing",query("eff_jing",  me), me);
                if( query("neili", me)<query("max_neili", me) )
                        set("neili", query("max_neili", me), me);
                /*
                me->add("neili",query("max_neili", me)/2-
                                 query("neili", me)/2);
                */
                message("vision", me->name() + "一覺醒來，精力充沛"
                                  "地活動了一下筋骨。\n",
                        environment(me), ({ me }));
                write("你一覺醒來，只覺精力充沛。該活動一下了。\n");
                set("last_sleep", time(), me);
        } else
        {
                message("vision", me->name() + "迷迷糊糊的睜開眼睛，"
                                  "懶散無神的爬了起來。\n",
                        environment(me), ({ me })); 
                write("你迷迷糊糊的睜開雙眼，爬了起來。\n");
        }
        me->write_prompt();
}

int help(object me)
{
        write(@HELP
指令格式 : sleep
 
顧名思義，這個指令是用來睡覺的。
HELP );
        return 1;
}
