// eval.c


inherit F_DBASE;
inherit F_CLEAN_UP;

string doith(string arg);

int main(object me, string arg)
{
        string file, filename, err;
        mixed  ret;
        int    cost;

        if ( ! SECURITY_D->valid_grant(me, "(arch)") ) 
                return 0; 

        if( !me->is_admin() )
                return notify_fail("你不能使用該命令。\n"); 

        if( !arg )
                return notify_fail("指令格式: eval <LPC 命令>\n");

        seteuid(geteuid(this_player(1)));
        filename=user_path(query("id", me));

        if( get_dir(filename) == 0 )
                        return notify_fail("你沒有私人工作目錄，不能使用此指令！\n");

        filename+=("eval_"+query("id", me)+".c");

        file = @EndText

// This file is made by the "eval" command.

#include <ansi.h>
#include <command.h>
#include <function.h>
#include <localtime.h>
#include <origin.h>
#include <room.h>
#include <type.h>
#include <user.h>
#include <eval.h> 

inherit F_CLEAN_UP;

mixed eval(string euid)
{
        seteuid(euid);
                {
EndText
                + doith(replace_string(arg, "\n", "")) + ";\n\t}\n}\n";


        seteuid(geteuid(this_player(1)));

        if (ret=find_object(filename)) destruct(ret);

        write_file(filename, file, 1);

        cost = eval_cost();
        err = catch( ret = call_other(filename, "eval", geteuid(this_player(1))));
        cost -= eval_cost();
        if (!err)
        {
                        write(sprintf("傳回值為: %O\n執行指令數：%d\n執行成功\。\n", ret,cost));
                rm(filename);
                if( ret=find_object(filename) ) destruct(ret);
                set("channel_id", sprintf("%s(%s)", me->name(),
                        capitalize(query("id", me))));
                CHANNEL_D->do_channel(this_object(), "sys",
                        sprintf("eval %s", arg));
        }
        else write("執行失敗！\n");
        return 1;
}


string doith(string arg) {

        int i;    // pointer to string within array containing an exploded bit
        int j;    // pointer to character within a given string
        int cnt;  // current count of (+1) ('s and (-1) )'s
        int poq;  // (waiting on) parethesisisis or quote; dual state
        string *inp = explode(arg, ";");

        for (i=0; i<sizeof(inp); i++) {
                for (j=0; j<strlen(inp[i]); j++) {
                        if(!poq && inp[i][j] == ')') cnt --;
                        if(!poq && inp[i][j] == '(') cnt ++;
                        if(inp[i][j] == '\\' && inp[i][j+1] == '"') j+=2;
                        if(inp[i][j] == '"') poq = (!poq);  // toggle poq state
                        if(strlen(inp[i])==j+1) {
                                if(sizeof(inp) == i+1) {
                                        if (cnt>0)
                                                write("!!!!!! 你多寫了 "+cnt+"一個左括號「(」。!!!!!!\n");
                                        else if(cnt<0)
                                                write("!!!!!! 你多寫了 "+(-cnt)+ "一個右括號「)」。!!!!!!\n");
                                        else if(poq)
                                                write("!!!!!! 字串不正常結束 !!!\n");
                                        // error or no error we return here at the end
                                        return "\t"+implode(inp, ";\n\t");
                                                                        }
                                else if (poq || cnt)
                                        inp[i] = inp[i] + ";"+ inp[i+1], inp -= ({inp[i+1]});
                        }
                }
        }
}


int help(object me)
{
write(@HELP
指令格式 : eval <LPC 命令>

執行指定的 LPC 命令。

例如：evalthis_player()->set("test",({"test_data"}) )

HELP );
    return 1;
}
