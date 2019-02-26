// cat.c
// updated by doing

#include <ansi.h>
int main(object me, string arg)
{
        string file;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (me != this_player())
                return 0;

        if (! arg) return notify_fail("指令格式 :cat <檔案名>\n");
        file = resolve_path(query("cwd", me), arg);
        if (file_size(file) < 0)
                return notify_fail("沒有這個檔案。\n");

        if (! SECURITY_D->valid_read(file, me, "cat"))
                return notify_fail("沒有這個檔案。\n");

        if (file_size(file) > 128000)
                write("文件太長，請用 more 指令查看。\n");
        else   {
                write(WHT "開始閲讀文件：" +  file + "\n" NOR);
                me->start_more(read_file(file));
                write(WHT "閲讀文件完畢。\n" NOR);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 :cat <檔案名>

這個指令讓你可以查閲一個文件的內容。

see also: more
HELP );
    return 1;
}