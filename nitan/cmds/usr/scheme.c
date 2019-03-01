// scheme.c

#include <ansi.h>

inherit F_CLEAN_UP;

private void done_input(object me, string text);
private void user_quit(object me);
int  continue_scheme(object me);
int  cancel_schedule(object me);

int main(object me, string arg)
{
        object ob;
        object env;
        string schedule;

        if (wizardp(me) && 0)
                return 0;

        seteuid(getuid());

        if (! arg)
        {
                if( !stringp(schedule=query("schedule", me)) )
                {
                        write("你目前並沒有制訂任何計劃。\n");
                        return 1;
                }

                write("你目前制訂的計劃如下：\n" + schedule);
                return 1;
        }

        if (sscanf(arg, "show %s", arg) == 1)
        {
                if (! wizardp(me))
                        return notify_fail("你無權查看他人制訂的計劃。\n");

                if (! objectp(ob = find_player(arg)))
                        return notify_fail("沒有這個玩家。\n");

                if( !stringp(schedule=query("schedule", ob)) )
                {
                        write("這個玩家沒有制定計劃。\n");
                        return 1;
                }

                write((ob == me?"你":(ob->name(1)+"("+query("id", ob)+")"))+
                      "現在制訂的計劃如下：\n" + schedule);
                if( query("doing", ob) == "scheme" )
                        write("該計劃目前正在執行中。\n");

                return 1;
        }

        if (arg == "clear")
        {
                if( query("doing", me) == "scheme" )
                        return notify_fail("你現在正在執行計劃，請先停下來再清除它。\n");

                delete("schedule", me);
                write("Ok.\n");
                return 1;
        }

        if (arg == "edit")
        {
                if( query("doing", me) == "scheme" )
                        return notify_fail("你現在正在執行計劃，請先停下來再修改。\n");

                write("請輸入你將要執行的計劃：\n");
                me->edit((: done_input, me :));
                return 1;
        }

        if (arg == "start")
        {
                if( !stringp(schedule=query("schedule", me)) )
                        return notify_fail("你目前還沒有制訂計劃。\n");

                if( query("doing", me) )
                        return notify_fail("你現在正在忙于鍛煉，不能開展新計劃。\n");

                env = environment(me);
                if (! env)
                        return notify_fail("你現在什麼都做不了。\n");

                if (env->is_chat_room())
                        return notify_fail("你不能在聊天室裡面執行計劃。\n");

                if( !query("sleep_room", env) )
                        return notify_fail("你必須在能夠休息的地方才能執行計劃。\n");

                if( !query("no_fight", env) )
                        return notify_fail("你必須在安全的地方才能執行計劃。\n");

                if( query("combat_exp", me)<50000 )
                        return notify_fail("你的實戰經驗太淺薄，還是先好好鍛煉鍛煉再說吧。\n");

                if( query("potential", me)-query("learned_points", me)<100 )
                        return notify_fail("你的潛能太少，難以開展計劃。\n");

                if (sizeof(filter_array(all_inventory(env), (: playerp :))) > 12)
                        return notify_fail("這裡的人實在太多了，你難以靜心開展計劃。\n");

                addn("learned_points", 100, me);

                // 執行計劃
                write("你開始執行計劃。\n");
                set("startroom", base_name(env), me);
                CLOSE_D->user_closed(me);
                me->set_short_desc(0);
                continue_scheme(me);
                return 1;
        }

        return notify_fail("非法的命令參數。\n");
}

// 開始執行計劃
int continue_scheme(object me)
{
        string schedule;
        string *scs;

        if( !stringp(schedule=query("schedule", me)) )
                return 0;

        scs = explode(schedule, "\n");
        scs = filter_array(scs, (: replace_string($1, " ", "\n") != "" :));
        if (sizeof(scs) < 1)
        {
                write("這是一份空計劃，你沒什麼好做的。\n");
                return 0;
        }

        set("doing", "scheme", me);
        set_temp("scs", scs, me);
        set_temp("scs_step", 0, me);
        delete_temp("scs_repeat", me);
        me->set_override("unconcious", (: call_other, __FILE__, "cancel_schedule" :));
        me->set_override("die", (: call_other, __FILE__, "cancel_schedule" :));
        return 1;
}

// 中止計劃
int cancel_schedule(object me)
{
        me->delete_override("unconcious");
        me->delete_override("die");

        if( !query("schedule", me) )
                return 0;

        CLOSE_D->user_opened(me);

        if (! interactive(me))
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 0);

        return 0;
}

// 執行計劃中
void execute_schedule(object me)
{
        mapping my, my_temp;
        string *scs;
        int scs_step;
        string *scs_repeat;
        string cmd, cmd_case;
        int i;
        int count;
        int pay;

        if (! objectp(me) || previous_object() != me)
                return;

        if (me->is_busy() || ! living(me))
                return;

//#ifndef NO_FEE
#ifdef DB_SAVE 
        if( !interactive(me) &&
            /*!me->is_vip() &&*/ query("online_time", me) <= query("offline_time", me)*3 ){
                cancel_schedule(me);
                return;
        }
#endif

        my = me->query_entire_dbase();
        my_temp = me->query_entire_temp_dbase();

        if (time() - (int)my_temp["scheme_last_fail"] < 5)
                return;

        if (my["food"] < 100 || my["water"] < 100)
        {
                write("你覺得肚子有點餓了，看來要找點吃的東西了。\n");
                pay = 2000;
                if( query("family/family_name", me) == "段氏皇族" )
                        pay = 100;
                else
                        pay = pay * 100 / (me->query_skill("higgling", 1) + 100);
                
                if (MONEY_D->player_pay(me, pay) != 1)
                {
                        write("你發現自己帶的錢不夠了，看來只好先去弄些錢了。\n");
                        cancel_schedule(me);
                        return;
                }
                write("你掏出一些錢，找了一位閒人讓他幫你準備了一些食物。\n");

                // 補充食物和水
                my["food"]  = me->max_food_capacity();
                my["water"] = me->max_water_capacity();
                me->start_busy(10 + random(10));
                return;
        }

        if (! arrayp(scs = my_temp["scs"]))
        {
                if (! continue_scheme(me))
                        cancel_schedule(me);
                return;
        }

        scs_step = my_temp["scs_step"];
        if (scs_step < 0 || scs_step >= sizeof(scs))
                scs_step = 0;

        // 取第 n 步驟
        cmd = scs[scs_step];
        cmd = me->process_input(cmd);
        if (sscanf(cmd, "%s:%s", cmd, cmd_case) != 2)
                cmd_case = "IGNORE";

        // 顯示準備執行的命令
        tell_object(me, me->prompt() + HIY + cmd + NOR "\n");

        switch (cmd)
        {
        case "REPEAT":
                // 開始循環
                count = 1;
                for (i = scs_step + 1; i < sizeof(scs); i++)
                {
                        if (scs[i] == "LOOP")
                        {
                                if (--count < 1)
                                break;
                        }
                        if (scs[i] == "REPEAT")
                                count++;
                }

                if (count > 0)
                {
                        write("計劃中 repeat 沒有找到與之匹配的 loop 命令，無法繼續執行。\n");
                        cancel_schedule(me);
                        break;
                }

                if (! arrayp(my_temp["scs_repeat"]))
                        my_temp["scs_repeat"]  = ({ ({ scs_step, i }) });
                else
                if (sizeof(my_temp["scs_repeat"]) < 12)
                        my_temp["scs_repeat"] += ({ ({ scs_step, i }) });
                else
                {
                        write("循環嵌套的層次太多，你的計劃書好復雜，執行不了。\n");
                        cancel_schedule(me);
                        break;
                }

                write("開始循環.\n");
                break;

        case "LOOP":
                // 循環執行
                if (! arrayp(scs_repeat = my_temp["scs_repeat"]) ||
                    sizeof(scs_repeat) < 1)
                {
                        write("沒有找到計劃中與之匹配的 repeat 命令。\n");
                        cancel_schedule(me);
                        return;
                }

                scs_step = scs_repeat[sizeof(scs_repeat) - 1][0];
                write("Loop.\n");
                break;

        case "BREAK":
                // 跳出該循環
                if (! arrayp(scs_repeat = my_temp["scs_repeat"]) ||
                    sizeof(scs_repeat) < 1)
                {
                        write("沒有找到計劃中與之匹配的 repeat-loop 命令。\n");
                        cancel_schedule(me);
                        return;
                }

                scs_step = scs_repeat[sizeof(scs_repeat) - 1][1];
                my_temp["scs_repeat"] = scs_repeat[0..<2];
                write("Ok.\n");
                break;

        default:
                // 執行第 n 步，並視情況看下一步是否執行第二操作
                if (! me->force_me(cmd))
                {
                        // 執行失敗時的命令
                        if (cmd_case != "IGNORE")
                                tell_object(me, me->prompt() + HIY + cmd_case + NOR "\n");

                        switch (cmd_case)
                        {
                        case "RETRY":
                                my_temp["scheme_last_fail"] = time();
                                return;

                        case "CONTINUE":
                                // 循環執行
                                if (! arrayp(scs_repeat = my_temp["scs_repeat"]) ||
                                    sizeof(scs_repeat) < 1)
                                {
                                        write("沒有找到計劃中與之匹配的 repeat 命令。\n");
                                        cancel_schedule(me);
                                        break;
                                }

                                scs_step = scs_repeat[sizeof(scs_repeat) - 1][0];
                                write("Loop.\n");
                                break;

                        case "BREAK":
                                // 跳出該循環
                                if (! arrayp(scs_repeat = my_temp["scs_repeat"]) ||
                                    sizeof(scs_repeat) < 1)
                                {
                                        write("沒有找到計劃中與之匹配的 repeat-loop 命令。\n");
                                        cancel_schedule(me);
                                        break;
                                }

                                scs_step = scs_repeat[sizeof(scs_repeat) - 1][1];
                                my_temp["scs_repeat"] = scs_repeat[0..<2];
                                write("Ok.\n");
                                break;

                        case "IGNORE":
                                // 執行命令忽略失敗情況
                                break;

                        default:
                                me->force_me(cmd_case);
                                break;
                        }
                        // 命令失敗時執行 cmd_case 完畢。
                }
                // 執行玩家命令完畢
        }

        if (++scs_step >= sizeof(scs))
        {
                write("計劃執行完畢。\n");
                cancel_schedule(me);
                return;
        }

        my_temp["scs_step"] = scs_step;
}

private void done_input(object me, string text)
{
        string *strs;

        if (! stringp(text))
        {
                tell_object(me, "你沒有輸入任何新的計劃。\n");
                return;
        }

        if (strlen(text) > 400)
        {
                tell_object(me, "你這份計劃太長了，請重新設置一個短一些的。\n");
                return;
        }

        strs = explode(text, "\n");
        strs = filter_array(strs, (: replace_string($1, " ", "") != "" :));
        text = implode(strs, "\n") + "\n";

        set("schedule", text, me);
        tell_object(me, "你設置了一份新的計劃。\n");
}

void user_quit(object me)
{
        if (! is_root(previous_object()) &&
            previous_object() != me)
                return;

        if (! objectp(me))
                return;

        me->force_me("quit");

        if (objectp(me) && ! interactive(me))
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 5);
}

int help (object me)
{
        write(@HELP
指令格式 : scheme [<edit> | <start> | <clear> | <show> <玩家>]
 
設定或開始你的計劃。如果你需要長時間的讀書或是練習技能，可以
使用計劃來完成，具體請參見 help schedule。

edit  : 設定計劃
start : 開始執行計劃
clear : 清除目前的計劃
show  : 顯示某個玩家的計劃，只有巫師才能使用這個命令。

執行計劃期間可以使用 halt 命令中止你正在進行的計劃。

see also: halt, breakup, purchase
HELP );
        return 1;
}
