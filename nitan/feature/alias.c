// alias.c
// Written by Lonely@nitan.org

#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <message.h>
#include <shell.h>

#define MAX_ALIASES             40
#define HISTORY_BUFFER_SIZE     500
#define MAX_DO_COMMANDS         20

#define HISTORY_CMD             0
#define HISTORY_TIME            1

mapping alias;
nosave string *command_history = allocate(0);
nosave int total_command_count;
nosave string last_input, orginal_input;
nosave int last_cmd;
nosave int direct_command;
nosave string *no_busy_cmds = ({
        "hp","score","inventory","look","l","skills","who",
        "id","save","time","uptime","wizlist","version",
        "tell","reply","say",
});

// 最後的輸入命令(已經經過ALIAS處理)
string query_last_input() { return last_input; }

// 最後的輸入原始字符串(已經經過命令確認：/或//打頭)
string query_orginal_input() { return orginal_input; }

// 是否是控制命令(以/或//打頭)
int is_direct_command() { return direct_command; }

string process_input(string str);

string remove_leadspace(string arg)
{
        int i;

        if( !stringp(arg) || arg =="" )
                return "";
        for( i = 0; i < strlen(arg); i++ )
                if( arg[i..i] != " " )
                        return arg[i..strlen(arg)];
        return "";
}
nomask string process_history(int i)
{
        int size = sizeof(command_history);
        string cmd;
        
        // 順序由後往前
        if( i < 0 )
        {
                i = -i;
                if( i < 1 ) i = 1;
                else if( i > size ) i = size;
                cmd = (string)command_history[<i][HISTORY_CMD];
        }
        // 順序由前往後
        else if( i > 0 )
        {
                if( i > total_command_count || i < 1 || i <= total_command_count - HISTORY_BUFFER_SIZE )
                {
                        tell(this_object(), "指令歷程范圍錯誤。\n");
                        return 0;
                }
                if( total_command_count >= HISTORY_BUFFER_SIZE )
                        i -= (total_command_count - HISTORY_BUFFER_SIZE);

                cmd = (string)command_history[i-1][HISTORY_CMD];
        }
        else
        {
                if( size > 0 )
                {
                        cmd = (string)command_history[<1][HISTORY_CMD];
                }
                else
                {
                        tell(this_object(), pnoun(2, this_object()) + "尚未下達任何指令。\n");
                        return 0;
                }
        }
        tell(this_object(), cmd + "\n");
        return cmd;
}

nomask string process_input_basic_parse(string cmd) /* Return 0 if break command input */
{
        switch(cmd[0]) 
        {
                case ''':       //'
                        cmd = "say " + cmd[1..];
                        break;
                case '\"':      //"
                        cmd = "tell " + cmd[1..];
                        break;
                case ']':
                        if( cmd[1] == ']' )
                                cmd = "chat* " + cmd[2..];
                        else
                                cmd = "chat "+ cmd[1..];
                        break;
                case '!':
                        // 指令歷程
                        {
                                int i;
                                sscanf(cmd, "!%d", i);
                                cmd = process_history(i);
                        }
                default:
                        break;
        }
        return cmd;
}

nomask void process_input_event()
{
        mapping waitback_list;
        object me = this_object();

        if( !mapp(query_temp("waitback_list")) ) return;
        else {
                int time = time();
                int wait_time;
                string msg = "";
                string wait_msg, chinese_time;
                string this_idname = me->query_idname(1);

                waitback_list = query_temp("waitback_list");
                waitback_list = filter(waitback_list, (: objectp($1) :));

                foreach( object usr, mapping info in waitback_list ) {
                        wait_time = info["time"];
                        wait_msg = info["msg"];

                        chinese_time = time_period(time - wait_time);

                        tell_object(usr, HIY "你等了" + chinese_time + "後，" + this_idname + HIY "終于回神了。\n" +
                                         (wait_msg ? "\n留言：" + wait_msg : "") + "\n\a" NOR);
                        msg += HIY + usr->query_idname(1) + HIY "花了" + chinese_time + "等著你回神。\n" +
                                         (wait_msg ? "\n留言：" + wait_msg : "") + "\n\a" NOR;
                }
                //call_out((: tell(this_object(), $(msg)) :), 0);
                tell_object(me, msg);
                delete_temp("waitback_list");
        }
}

nomask int process_input_do(string verb, string args)
{
        if( verb != "do" ) return 0;
        
        if( args )
        {
                int do_times;
                int total_cmds;

                foreach( string action in explode(args, ",") )
                {
                        do_times = 1;
                        sscanf(action, "%d %s", do_times, action);

                        action = remove_leadspace(action);

                        if( do_times > MAX_DO_COMMANDS ) do_times = MAX_DO_COMMANDS;

                        if( !strsrch(action, "do ") )
                        {
                                tell_object(this_object(), "指令 do 中不能再有 do 的指令。\n");
                                return 1;
                        }

                        while( do_times-- && ++total_cmds )
                        {
                                if( total_cmds > MAX_DO_COMMANDS && !wizardp(this_object()) )
                                {
                                        tell_object(this_object(), "你不能一次下超過 "+MAX_DO_COMMANDS+" 個指令。\n");
                                        return 1;
                                }
                                // 必須command，否則add_action中query_verb出問題 by Lonely
                                command(process_input(action));
                        }
                }
        }
        else
                tell_object(this_object(), "請輸入要連續下達的指令。\n");

        return 1;
}

string process_input(string str)
{
        string verb, doargs, *args;
        string cmd, argstr;
        object me, ob;
        int i, j;

        me = this_object();
        notify_fail("什麼？\n"); 
        clear_written();
        
        if( !living(me) || query_temp("disable_input") ) return "";

        if( !wizardp(me) && query_temp("command_delay") > time() ) return "";

        if( query_temp("dizziness", me) )
        {
                tell_object(me, "你目前處于眩暈狀態，無法進行任何動作。\n");
                return "";
        }

        // 任何一個指令輸入後的觸發
        process_input_event();

        /*
        if( me->is_busy() && (member_array(str, no_busy_cmds) == -1) ) {
                tell_object(me, BUSY_MESSAGE);
                return "";
        }
        */

        // 記錄最原始的輸入
        if( str[0] == '/' ) {
                direct_command = 1;
                if (str[1] == '/') str = str[2..<1]; else
                                   str = str[1..<1];
        } else direct_command = 0;

        orginal_input = str;

        // attach system ?
        if( me->is_attach_system() ) {
                me->detach_system();
                tell_object(me, HIR "用戶終止了當前執行的進程。\n" NOR);
        }

        if( str == "" ) return str;

        if( me->reject_command() ) {
                tell_object(me, RED "\n\n高處不勝寒突然在一陣煙霧中出現。\n\n\n\n高處不勝寒喝道：你刷屏過快，接下來十秒內系統不再接受你的指令！\n\n" NOR);
                set_temp("command_delay", time()+10);
                message_vision("$N突然一陣頭暈目眩，傻傻的站在這不動了。\n", me);
        }

        if( query_temp("big5") )
                //str = B2G(str);
                str = LANGUAGE_D->Big52GB(str);

        //str = remove_fringe_blanks(str);
        str = remove_leadspace(str);
        
        // 基本語法處理
        str = process_input_basic_parse(str);

        if( mapp(alias) ) {
                if( !undefinedp(alias[str]) )
                        str = replace_string( alias[str], "$*", "" );
                else if( sscanf(str, "%s %s", cmd, argstr) == 2 && !undefinedp(alias[cmd]) ) {
                        cmd = replace_string( alias[cmd], "$*", argstr );
                        args = explode(argstr, " ");
                        if( (j = sizeof(args)) )
                                for( i=0; i<j; i++ )
                                        cmd = replace_string( cmd, "$" + (i+1), args[i] );
                        str = cmd;
                }
        }
        /*
        if( str[0] == '!' ) {
                if( pointerp(command_history) && sizeof(command_history) ) {
                        if( sscanf(str, "!%d", i) )
                                str = (string)command_history[(HISTORY_BUFFER_SIZE + last_cmd - i) % HISTORY_BUFFER_SIZE];
                        else
                                str = command_history[last_cmd];
                } else
                        return "";
        } else {
                if( !pointerp(command_history) ) command_history = allocate(HISTORY_BUFFER_SIZE);
                last_cmd = (last_cmd + 1) % HISTORY_BUFFER_SIZE;
                command_history[last_cmd] = str;
        }
        */
        // 記錄指令歷程
        if( sizeof(command_history) >= HISTORY_BUFFER_SIZE )
                command_history = command_history[1..] + ({ ({ str, time() }) });
        else
                command_history += ({ ({ str, time() }) });

        total_command_count++;
 
         // 處理指令
        if( sscanf(str, "%s %s", verb, doargs) != 2 ) verb = str;

        if( !doargs || !doargs[0] ) doargs = 0;

        // 處理連續指令
        if( process_input_do(verb, doargs) ) return "";


        if( wizardp(me) && query("env/use_shell") )
                str = parse_shell(str);

        last_input = (string)ALIAS_D->process_global_alias(str);                 
                       
        log_command(last_input);
        return last_input;
}

nomask void clear_history()
{
        command_history = allocate(0);
}

nomask string *query_history()
{
        object this_player = this_player(1);
        
        if( !objectp(this_player) ) return 0;
        
        if( wiz_level(this_player->query_id(1)) < wiz_level(this_object()->query_id(1)) )
                return 0;

        return copy(command_history);
}

nomask int total_command_count()
{
        return total_command_count;
}

int set_alias(string verb, string replace)
{
        if( !replace ) {
                if( mapp(alias) ) map_delete(alias, verb);
                return 1;
        } else {
                if( !mapp(alias) ) alias = ([ verb:replace ]);
                else if( sizeof(alias) > MAX_ALIASES )
                        return notify_fail("您設定的 alias 太多了，請先刪掉一些不常用的。\n");
                else alias[verb] = replace;
                return 1;
        }
}

mapping query_all_alias()
{
        return alias;
}

int set_ALIAS(mapping data)
{
        if( !mapp(data) ) return 0;
        alias = data;
        return 1;
}
