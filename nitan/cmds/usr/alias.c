// alias.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i;
        mapping alias;
        string verb, replace, *vrbs;

        if (! arg)
        {
                alias = me->query_all_alias();
                if (! sizeof(alias))
                {
                        write("你目前並沒有設定任何 alias。\n");
                        return 1;
                } else
                {
                        write("你目前設定的 alias 有：\n");
                        vrbs = sort_array(keys(alias), 1);
                        for (i = 0; i < sizeof(vrbs); i++)
                                write(sprintf("%-15s = %s\n", vrbs[i], alias[vrbs[i]]));
                        return 1;
                }
        }

        /*
        arg = replace_string(arg, "\"", ""); 
        arg = replace_string(arg, "\\", ""); 
        */
        if (strsrch(arg, "\"") != -1 || strsrch(arg, "\\") != -1)
        {
                write("你不能夠設置包含\"和\\的別名！\n");
                return 1;
        }

        if (sscanf(arg, "%s %s", verb, replace) != 2)
        {
                me->set_alias(arg, 0);
                write("你取消了 " HIR + arg + NOR " 這個替代命令。\n");
        }
        else if (verb == "alias")
                return notify_fail("你不能將 \"alias\" 指令設定其他用途。\n");
        else if (verb == "")
                return notify_fail("你要設什麼 alias？\n");
        else if (stringp(COMMAND_D->find_command(verb, PLR_PATH)))
                return notify_fail("動詞 " + verb + " 是一個常用命令，你不能替代它。\n");
        else
        {
                if (! me->set_alias(verb, replace))
                {
                        // failed.
                        return 0;
                }
                write("今後你用 " HIR + verb + NOR " 來替代 " HIG +
                      replace + NOR " 命令。\n");
        }
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式 : alias <欲設定之指令> <系統提供之指令>
 
有時系統所提供之指令需要輸入很長的字串, 在使用時(尤其是經常用到的)
或許會感覺不方便, 此時你(你)即可用此一指令設定並替代原有之指令。
 
範例:
        'alias sc score' 會以 sc 取代 score 指令。
        'alias' 後不加參數則列出你所有的替代指令。
        'alias sc' 會消除 sc 這個替代指令。 (如果你有設的話)
 
其中可以用 $1, $2, $3 .... 來取代第一、第二、第三個參數，或是 $* 取代
所有的參數，如：
        'alias pb put $1 in $2'

則每當你(你)打：
        pb bandage bag

就會取代成：
        put bandage in bag
        
HELP );
        return 1;
}