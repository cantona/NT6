// /cmds/arch/clearcoor.c

// Created by Constant Jan 8 2001

inherit F_CLEAN_UP;

int clearfile(object me,string file);

int main(object me, string arg, int recur_flag)
{
        int i, j;
        string dir;
        mixed *file;
        int recur = 0;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        if (arg == "-d") {
                recur = 1;
                arg = "";
        }

        if (arg && sscanf(arg, "-d %s", arg))
                recur = 1;

        if (arg && sscanf(arg, "-s %s", arg)) {
                arg=resolve_path(query("cwd", me),arg);
                if (!sscanf(arg, "%*s.c"))
                        arg += ".c";
                if (file_size(arg) > 0) {
                        notify_fail("處理完畢。\n");
                        return clearfile(me ,arg);
                } else
                        return notify_fail("沒有這個文件。\n");
        }

        dir=resolve_path(query("cwd", me),arg);

        if ( file_size(dir) == -2 && dir[strlen(dir)-1] != '/' )
                dir += "/";

        file = get_dir(dir, -1);

        if (!sizeof(file)) {
                if (file_size(dir) == -2)
                        return notify_fail("目錄是空的。\n");
                else
                        return notify_fail("沒有這個目錄。\n");
        }

        i = sizeof(file);
        while (i --) {
                if (file[i][1] == -2)
                        file[i][0] += "/";
        }

        write("正在處理目錄：" + dir + "\n");

        if (sizeof(file)) {
                for(i = 0,j = sizeof(file); i < j; i ++) {
                        if (file[i][1]!=-2 && sscanf(file[i][0], "%*s.c")
                                && file[i][0][strlen(file[i][0])-1] == 'c'
                                && file[i][0][strlen(file[i][0])-2] == '.')
                                clearfile(me, dir + file[i][0]);
                        else if (file[i][1] == -2 && recur)
                                call_other(__FILE__, "main", me, dir+file[i][0], 1);
                }
        }

        return 1;
}

int clearfile(object me, string file)
{
        object obj;
        int i, x, y, z;
        string *in_text, *temp_text;
        string out_text;

        reset_eval_cost();

        if (!(obj = find_object(file)))
                obj = load_object(file);

        if( !obj || !query("coor", obj) )
                return 0;
        else {
                x=query("coor/x", obj);
                y=query("coor/y", obj);
                z=query("coor/z", obj);
        }

        in_text = explode(read_file(file), "\n");

        reset_eval_cost();

        write("\t正在整理文件" + file);
        for (i = 0; i < sizeof(in_text); i ++) {
                if (strsrch(in_text[i], "set(\"coor/") == -1) {
                        if (nullp(temp_text))
                                temp_text = ({in_text[i]});
                        else
                                temp_text += ({in_text[i]});

                } else
                        write(".");
        }

        out_text = implode(temp_text, "\n");
        out_text = replace_string(out_text, "setup()",
                        sprintf("set(\"coor/x\", %d);\n\tset(\"coor/y\", %d);\n\tset(\"coor/z\", %d);\n\tsetup()",
                        x, y, z));

        write_file(file, out_text, 1);

        write("完畢。\n");
        return 1;
}

int help(object me)
{
write(@HELP
指令格式: clearcoor [-d | -s] [<路徑名> | <文件名>]

清除指定目錄下所有的文件的多餘座標，如果不指定
目錄, 則使用當前目錄。如果帶參數-d，則連帶處理
子目錄。如果指定參數-s，則只處理該文件。

HELP
);
return 1;
}