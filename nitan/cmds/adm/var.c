// define var
// poet modified to use F_SHELL
// poet modified to use free command style
// var.c

#include <shell.h>

int main(object me, string arg)
{
        mixed result;
        string name, value;
        int index;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
        {
                mapping vars;
                string content;


                vars = me->query_all_vars();

                content = "您當前設置的私有變量有：\n";

                content += sprintf("me\t: %s\t== %O\n", typeof(me), me);
                content += sprintf("here\t: %s\t== %O\n",
                                   typeof(environment(me)), environment(me));
                foreach(name in keys(vars))
                {
                        if (undefinedp(vars[name]) || nullp(vars[name]))
                                content += sprintf("%s\t: void\n", name);
                        else
                                content += sprintf("%s\t: %s\t== %O\n", name,
                                                   typeof(vars[name]), vars[name]);
                }

                tell_object(me, content);
                return 1;
        }

        index = strsrch(arg, '=');

        if (index == -1)
        {
                name = arg;
        } else
        {
                name = arg[0..(index-1)];
                value = arg[(index+1)..<1];
        }

        name = replace_string(name, " ", "");

        if (name == "me" || name == "here")
        {
                return notify_fail("這是系統預定義的私有變量。\n");
        }

        if (! value)
        {
                if (undefinedp(result) || nullp(result))
                        printf("%s\t: void\n", name);
                else
                        printf("%s\t: %s\t== %O\n", name,
                               typeof(me->query_var(name)), me->query_var(name));
                return 1;
        }

        if (value == "none" || value == " none"
        ||  value == "null" || value == " null")
        {
                me->delete_var(name);
                printf("Delete var '%s' Ok.\n", name);
                
                return 1;
        }

        if (me->query_var_count() >= MAX_VAR_COUNT)
                return notify_fail("請不要設置過多的私有變量。\n");

        result = me->evaluate_shell(value, 0);

        result = me->set_var(name, result);

        if (undefinedp(result) || nullp(result))
                printf("%s\t: void\n", name);
        else
                printf("%s\t: %s\t== %O\n", name, typeof(result), result);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : var name=value


這個指令可以設置私有變量，其中 value 的語法和 LPC 程序完全相同。
變量可以在 dual 或者內嵌 shell 中使用，或者 export 到環境變量中去。

單獨使用 var 命令列出目前的私有變量列表。

系統已預定義變量 me 和 here

HELP
        );
        return 1;
}
