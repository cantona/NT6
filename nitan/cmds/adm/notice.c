// This program is a part of NITAN MudLIB
// notice.c

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string msg)
{
        string *lines;
        string arg;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if( !msg || msg == "" )
        {
                if( file_size(NOTICE) < 0 )
                {
                        write("現在沒有設定任何連線通知\n");
                        write("--------------------------------------------\n\n");
                        return help(me);
                }

                arg = read_file(NOTICE);
                write("你現在所設定的連線通知是：\n");
                write("--------------------------------------------\n\n");

                if( strlen(arg) > 8190 )
                        me->start_more(arg);
                else
                        write(arg);

                return 1;
        }

        if( msg == "-rm" )
        {
                rm(NOTICE);
                write("通知已被清除!\n");
                return 1;
        }

        msg = replace_string(msg, "\\t", "\t");
        msg = replace_string(msg, "\\n", "\n");
        msg = replace_string(msg, "\"\"", "");

        lines = explode(msg, "\n");
        for( int i=0; i<sizeof(lines); i++ )
                if ( i % 2 == 0)
                        lines[i] = BLINK + REDYEL "█" NOR "  " + lines[i];
                else
                        lines[i] = BLINK + YELRED "█" NOR "  " + lines[i];

        msg = implode(lines, "\n") + "\n";
        msg = color_filter(msg);
        msg += NOR;
        write_file(NOTICE, msg, 1);
        write("連線通知加入完畢。\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: notice <通知內容>

改指令用來添加玩家連線後的通知信息，如無必要儘量少用
notice -rm 用來清除信息。
HELP
        );
        return 1;
}

