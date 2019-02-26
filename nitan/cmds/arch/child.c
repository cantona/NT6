// child.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object where, *list;
        int i, number;
        string option,str;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg)arg=query("cwf", me);
        if (! arg) return notify_fail("你要查看哪個文件？\n");
  
        if (sscanf(arg, "%s %s", option, str) != 2 || option != "-r")
        str = arg; 

        str=resolve_path(query("cwd", me),str);
        if (sscanf(str, "%*s.c") != 1) str += ".c";
                set("cwf", str, me);
      
        if (file_size(str) < 0)
                       return  notify_fail("沒有這個文件："  +  str  +  ")\n");

        list = children(str);
        number=sizeof(list);
        if (number)
        {
                for (i = 0; i < sizeof(list); i++)
                {
                        write((int)(i + 1) + ". " + file_name(list[i]) + " " +
                              query("name", list[i])+"("+
                              query("id", list[i])+") is at");
                        where = environment(list[i]);
                        if (where)
                        {
                                if( query("short", where) )
                                {
                                        write(query("short", where));
                                } else
                                {
                                        write(where->short());
                                }
                                write("(" + file_name(where) + ")\n");
                                if (option == "-r" && ! living(where))
                                {
                                        destruct(list[i]);
                                        write ("已經清除。\n");
                                }
                        } else
                        {
                                write("???\n");
                                if (option == "-r")
                                        destruct(list[i]);
                        }
                }
        } else
                write("沒有找到任何派生物件。\n");
        return  1;
}

int help(object me)
{
        write(@HELP
指令格式: child [-r] filename

列出一個文檔所有副本。
如果用-r參數，則銷燬所有不在活物身上的該文檔副本。

HELP );
        return 1;
}
