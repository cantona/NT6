// edit.c

#include <ansi.h>
inherit F_CLEAN_UP;

string string_name()
{
        return HIM "編輯器(Edit)";
}

int main(object me, string file)
{
        string dir;
        
        if (! SECURITY_D->valid_grant(me, "(apprentice)"))
                return 0;

        if (! file) return notify_fail("指令格式：edit <檔名>\n");
                
        if (in_edit(me)) return notify_fail("你已經在使用編輯器了。\n");

        file = resolve_path(query("cwd", me), file);

        if (! me->is_admin()) 
        {
                dir = SECURITY_D->query_site_privilege("edit");
                if( !dir && !sscanf(file, "/u/%*s") )
                        return notify_fail("你只能在你自己的目錄下編輯。\n");
                        
                if( dir != "all" && !sscanf(file, "/%s/%*s", dir) )
                        return notify_fail("你只能在你自己目錄以及在" + dir + "目錄下編輯。\n");
        }
        
        foreach (object user in users())
        if (file == in_edit(user))
                return notify_fail(HIM "共享沖突：" + user->name(1) + HIM "(" +
                        capitalize(query("id", user)) + ")" +
                        HIM "正在編輯該文件(" + file + ")。\n" NOR);

        printf("編輯文件：%s\n", file);
        CHANNEL_D->channel_broadcast("sys",
                sprintf("%s(%s)正在編輯文件(%s)。",
                me->name(1),
                capitalize(query("id", me)),
                file));

        seteuid(geteuid(me));
        set("cwf", file, me);
        SECURITY_D->backup_file(file);
        ed(file);

        log_file("static/edit", sprintf("%s %-9s edit %s from %s.\n",
                                        log_time(),
                                        geteuid(me), file,
                                        query_ip_name(me)));
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : edit <檔名>, edit here
利用此一指令可直接在線上編輯檔案。
                /向前搜索匹配項
                ?向後搜索匹配項
                =顯示當前所在行數
                a在當前行的後面添加
                A與'a'相似
                c修改當前行，替換查詢文本
                d刪除一行或多行
                e用另一個文件覆蓋當前文件
                E與'e'相似，但只在文件被子修改之後有效
                f顯示/改變當前文件的文件名
                g搜索並對匹配的行執行某種命令
                h幫助
                i在當前行前插入字符
                k用一個字符標記當前行
                l列出一行或多行（帶控制字符）
                m移動一行或多行到指定的位置（行號）
                n標記行號
                O同'i'
                o同 'a'
                p列出一定范圍的行
                q退出
                Q退出，而且不存
                r在文件尾部或指定行後讀入其它文件
                s搜索並替換
                set查詢、改變或存儲某種設定選項
                t拷貝一行或幾行到指定行數
                v搜索並對不匹配的行執行某種命令
                x存文件並退出
                w寫入當前文件（或指定文件）採用覆蓋
                W現'w'相似，採用追加
                z顯示20行，可用 . + - 三種標記
                Z顯示40行，可用 . + - 三種標記

HELP
        );
        return 1;
}
