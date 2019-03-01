// trigger.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define MAX_TRIGGER_CMDS  10
#define TRIGGER_CMD_SIZE  21

protected void done_input(object me, string text);
protected void user_quit(object me);
int  continue_trigger(object me);
int  cancel_trigger(object me);

int main(object me, string arg)
{
        object ob;
        object env;
        string msg, filename, file, *lines;
        string tg_msg, tg_cmd;
        int i, n, line;

        seteuid(getuid());

        filename=DATA_DIR+"trigger/"+query("id", me)+__SAVE_EXTENSION__;
        if( !arg) {
                if( file_size(filename) > 0 ) {
                        write(HIC"您目前已設定有的觸發如下：\n"NOR);
                        file = read_file(filename);
                        msg = HIW"";

                        lines = explode(file, "\n");
                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                        tg_cmd = replace_string(tg_cmd, ",", ";");
                                        msg += "-----------------------------------------------\n";
                                        msg += "(" + chinese_number(i+1) + ")\n";
                                        msg += HIY"觸發字符："HIW + tg_msg + "\n";
                                        msg += HIY"觸發指令："HIW + tg_cmd + "\n";
                                        msg += "-----------------------------------------------\n";
                                }
                        }

                        msg += "\n"NOR;
                        me->start_more(msg);

                        return 1;
                }
                else
                        return notify_fail(HIW"指令格式：trigger 觸發字符:執行指令\n"HIY"[提示：如需設置多個指令，每個指令之間用逗號[,]間隔開]\n"NOR);
        }

        if( arg == "clear" ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("你現在正在執行觸發，請先停下來再清除它。\n");

                delete("trigger", me);
                if( file_size(filename) >= 0 ) {
                        rm(filename);
                        write(HIW"成功清除觸發設置。\n"NOR);
                        return 1;
                } else {
                        write(HIW"你並沒有設置觸發。\n"NOR);
                        return 1;
                }
        }

        if( sscanf(arg, "rm %d", line) ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("你現在正在執行觸發，請先停下來再清除它。\n");

                if( file_size(filename) > 0 ) {
                        file = read_file(filename);
                        lines = explode(file, "\n");

                        if( line > sizeof(lines) )
                                return notify_fail(HIY"第 " + chinese_number(line) +" 條觸發設置不存在。\n"NOR);

                        msg = "";

                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( i + 1 == line ) {
                                        if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                                tg_cmd = replace_string(tg_cmd, ",", ";");
                                                write(HIR"你成功刪除第" + chinese_number(line) + "條觸發如下：\n");
                                                write("-----------------------------------------------\n");
                                                write(HIY"觸發字符："HIW + tg_msg + "\n");
                                                write(HIY"觸發指令："HIW + tg_cmd + "\n");
                                                write("-----------------------------------------------\n");
                                        }

                                        continue;
                                }

                                msg += lines[i] + "\n";
                        }
                        rm(filename);
                        write_file(filename, msg, 1);
                        return 1;
                }
                else
                        return notify_fail(HIY"你目前並沒有觸發設置。\n"NOR);
        }
        if( arg == "start" ) {
                if( file_size(filename) < 1 )
                        return notify_fail("你目前還沒有制訂觸發。\n");

                if( query("trigger", me) )
                        return notify_fail(HIY"你並沒有關閉觸發功能，不需要再開啟。\n"NOR);

                if( query("doing", me) )
                        return notify_fail("你現在正在忙于鍛煉，不能開展新觸發。\n");

                env = environment(me);
                if( !env )
                        return notify_fail("你現在什麼都做不了。\n");

                if( env->is_chat_room() )
                        return notify_fail("你不能在聊天室裡面執行計劃。\n");

                if( query("combat_exp", me)<5000 )
                        return notify_fail("你的實戰經驗太淺薄，還是先好好鍛煉鍛煉再說吧。\n");

                if( query("potential", me)-query("learned_points", me)<100 )
                        return notify_fail("你的潛能太少，難以開展觸發。\n");

                if( sizeof(filter_array(all_inventory(env), (: userp :))) > 12 )
                        return notify_fail("這裡的人實在太多了，你難以靜心開展觸發。\n");

                addn("learned_points", 100, me);

                file = read_file(filename);
                set("trigger", file, me);
                write(HIG"你開啟了觸發功能。\n"NOR);
                set("startroom", base_name(env), me);
                CLOSE_D->user_closed(me);
                me->set_short_desc(0);
                continue_trigger(me);
                return 1;
        }

        if( query("doing", me) == "trigger" )
                return notify_fail("你現在正在執行觸發，請先停下來再修改。\n");

        if( strlen(arg) > 300 )
                return notify_fail(HIY"你的觸發設定太長了，請控制在300個字節以內，\n"NOR);

        if( file_size(filename) > 0 ) {
                file = read_file(filename);
                lines = explode(file, "\n");

                if( sizeof(lines) >= TRIGGER_CMD_SIZE )
                        return notify_fail(HIY"你只能設置" + chinese_number(TRIGGER_CMD_SIZE) + "條觸發，需要刪除一些觸發才能繼續設置。\n"NOR);
        }

        if( sscanf(arg, "%s:%s", tg_msg, tg_cmd) ) {
                if( !tg_msg || !tg_cmd )
                        write(HIW"增加觸發失敗。\n"NOR);
                else
                if( write_file(filename, tg_msg + ":" + tg_cmd + "\n") ) {
                        tg_cmd = replace_string(tg_cmd, ",", ";");
                        write(HIG"你成功增加了一條觸發如下：\n");
                        write("-----------------------------------------------\n");
                        write(HIY"觸發字符："HIW + tg_msg + "\n");
                        write(HIY"觸發指令："HIW + tg_cmd + "\n");
                        write("-----------------------------------------------\n");
                }
                else
                        write(HIW"增加觸發失敗。\n"NOR);
        }
        else
                return notify_fail(HIW"指令格式：trigger 觸發字符:執行指令\n"HIY"[提示：如需設置多個指令，每個指令之間用逗號[,]間隔開]\n"NOR);

        return 1;

}

// 開始執行觸發
int continue_trigger(object me)
{
        if( !query("trigger", me) )
                return 0;

        set("doing", "trigger", me);
        me->set_override("unconcious", (: call_other, __FILE__, "cancel_trigger" :));
        me->set_override("die", (: call_other, __FILE__, "cancel_trigger" :));
        return 1;
}

// 中止觸發
int cancel_trigger(object me)
{
        me->delete_override("unconcious");
        me->delete_override("die");

        if( !query("trigger", me) )
                return 0;

        delete("trigger", me);
        delete_temp("trigger", me);
        CLOSE_D->user_opened(me);

        if( !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 0);

        return 0;
}

// 執行觸發中
void execute_trigger(object me)
{
        string cmd, *cmds, *run;
        string cmd_buffer;
        int i, n;

        if( !objectp(me) || previous_object() != me )
                return;

        if( !(cmd=query_temp("trigger", me)) )
                return;

#ifndef NO_FEE
        if( !interactive(me) &&
            !me->is_vip() && query("online_time", me) <= query("offline_time", me)*3){
                cancel_trigger(me);
                return;
        }
#endif

        cmds = explode(cmd, ",");
        n = sizeof(cmds);
        run = ({ });

        for( i=0; i<n; i++ ) {
                if( i >= MAX_TRIGGER_CMDS ) break;
                if( me->is_busy() || !living(me) ) break;
                if( query("jing", me)*100/query("max_jing", me)<5 || 
                    query("qi", me)*100/query("max_qi", me)<5 )
                        break;
                if( query_temp("block_msg", me) || me->is_block_cmds() )
                        break;

                me->force_me(cmds[i]);
                run += ({ cmds[i] });
        }

        cmds -= run;

        if( !arrayp(cmds) || !sizeof(cmds) ) {
                delete_temp("trigger", me);
        } else {
                cmd_buffer = implode(cmds, ",");
                set_temp("trigger", cmd_buffer, me);
        }

        return;
}

void user_quit(object me)
{
        if( !is_root(previous_object()) &&
            previous_object() != me )
                return;

        if( !objectp(me) )
                return;

        me->force_me("quit");

        if( objectp(me) && !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 5);
}

int help (object me)
{
       write(@HELP
指令格式：
[一]、增加一條觸發：trigger 觸發字符:執行指令
      例如：我想觸發“運功完畢”，也就是屏幕上出現“運功完畢”，我就
      讓他打坐練內，那麼我們可以如下面這麼設置：
      trigger 運功完畢:dazuo 100
      執行看看，你會發現只要屏幕上一出現“運功完畢”這些字，系統就會
      自動幫你用100點內力打坐。
      也許你會問：如果我想屏幕上出現“運功完畢”就先讀書一次再打坐，
      也就是屏幕上出現“運功完畢”時同時執行兩個指令，那怎麼設置呢？
      很簡單，你只需要把各個指令之間用逗號[,]間隔開就可以了。如下：
      trigger 運功完畢:study book,dazuo 100
      系統就會在屏幕上出現“運功完畢”時就先幫你讀書讀書一次再打坐了。
      當然也同離線計劃練功一樣也是支持 alias 簡化指令的。
[二]：查看設置的所有觸發：trigger
[三]：刪除一條觸發：trigger rm 數字
      說明：這個數字就是你要刪除的那條觸發的位置，可以通過查看你要刪
      除的那條觸發的位置。
[四]：刪除所有觸發：trigger clear
[五]：關閉觸發：halt
[六]：啟動觸發：trigger start

see also: scheme
HELP
        );
        return 1;
}
