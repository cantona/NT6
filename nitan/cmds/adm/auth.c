// auth.c
// Doing

#include <ansi.h>

inherit F_CLEAN_UP;

string  auth_msg(mapping ruler, mapping default_ruler, string euid, string status);
int     in_map(string usr, mapping m, string index);
int     remove_from_map(string usr, mapping m, string index);
mapping add_into_map(string usr, mapping m, string index);
void    reset_security();
string  title(string t);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        string msg;
        string dir;
        string para;
        string usr;
        string euid;
        string status;
        mapping dtr, der, dtw, dew; // t = trusted e = exclude
        mapping ctr, cer, ctw, cew; // r = read    w = write
        mapping etr, eer, etw, eew; // d = default e = extend  c = current
        int flag;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
                return notify_fail("你沒有權限訪問安全系統。\n");

        seteuid(geteuid(me));
        dtr = SECURITY_D->query_security("default_trusted_read");
        der = SECURITY_D->query_security("default_exclude_read");
        dtw = SECURITY_D->query_security("default_trusted_write");
        dew = SECURITY_D->query_security("default_exclude_write");
        etr = SECURITY_D->query_security("extend_trusted_read");
        eer = SECURITY_D->query_security("extend_exclude_read");
        etw = SECURITY_D->query_security("extend_trusted_write");
        eew = SECURITY_D->query_security("extend_exclude_write");
        ctr = SECURITY_D->query_security("trusted_read");
        cer = SECURITY_D->query_security("exclude_read");
        ctw = SECURITY_D->query_security("trusted_write");
        cew = SECURITY_D->query_security("exclude_write");
        if (! arg)
        {
                msg = "目前文件關于安全的配置信息(青色表示缺省配置)：\n";
                msg += HIR + title("讀取禁止") + NOR;
                msg += auth_msg(cer, der, 0, 0);
                msg += HIC + title("讀取許可") + NOR;
                msg += auth_msg(ctr, dtr, 0, 0);
                msg += HIR + title("寫入禁止") + NOR;
                msg += auth_msg(cew, dew, 0, 0);
                msg += HIC + title("寫入許可") + NOR;
                msg += auth_msg(ctw, dtw, 0, 0);
                write(msg);
                return 1;
        } else
        if (arg == "read")
        {
                msg = "目前文件關于安全的配置信息中讀取的設置(青色表示缺省配置)：\n";
                msg += HIR + title("讀取禁止") + NOR;
                msg += auth_msg(cer, der, 0, 0);
                msg += HIC + title("讀取許可") + NOR;
                msg += auth_msg(ctr, dtr, 0, 0);
                write(msg);
                return 1;
        } else
        if (arg == "write")
        {
                msg = "目前文件關于安全的配置信息中寫入的設置(青色表示缺省配置)：\n";
                msg += HIR + title("寫入禁止") + NOR;
                msg += auth_msg(cew, dew, 0, 0);
                msg += HIC + title("寫入許可") + NOR;
                msg += auth_msg(ctw, dtw, 0, 0);
                write(msg);
                return 1;
        }

        if (sscanf(arg, "%s %s %s", usr, dir, para) != 3)
        {
                para = 0;
                if (sscanf(arg, "%s %s", usr, dir) != 2)
                {
                        dir = 0;
                        usr = arg;
                }
        }

        if (dir == "-clear")
        {
                remove_from_map(usr, etr, 0);
                remove_from_map(usr, eer, 0);
                remove_from_map(usr, etw, 0);
                remove_from_map(usr, eew, 0);

                SECURITY_D->set_security("extend_trusted_read", etr);
                SECURITY_D->set_security("extend_exclude_read", eer);
                SECURITY_D->set_security("extend_trusted_write", etw);
                SECURITY_D->set_security("extend_exclude_write", eew);
                reset_security();

                write("清除了該用戶所有的訪問信息，採用缺省配置。\n");
                return 1;
        }

        if (dir)
        {
                dir = resolve_path(query("cwd", me), dir);
                dir = "/" + implode(explode(dir, "/") - ({ "" }), "/");
        }

        if (usr[0] == '(')
        {
                status = usr;
                euid = "Every";
        } else
        {
                status = wizhood(usr);
                euid = usr;
        }

        if (! dir)
        {
                msg = "目前關于" CYN + euid + status +
                      NOR "的權限(青色表示缺省配置)：\n";
                msg += HIR + title("讀取禁止") + NOR;
                msg += auth_msg(cer, der, euid, status);
                msg += HIC + title("讀取許可") + NOR;
                msg += auth_msg(ctw, dtw, euid, status);
                msg += HIR + title("寫入禁止") + NOR;
                msg += auth_msg(cew, dew, euid, status);
                msg += HIC + title("寫入許可") + NOR;
                msg += auth_msg(ctw, dtw, euid, status);
                write(msg);
                return 1;
        }

        if (! para)
        {
                msg = CYN + euid + status + NOR "對檔案("
                      YEL + dir + NOR ")的權限：";
                if (SECURITY_D->valid_read(dir, euid == "Every" ? status : euid, "ls"))
                        msg += WHT "可讀 " NOR;
                else
                        msg += HIR "禁止讀取 " NOR;

                if (SECURITY_D->valid_write(dir, euid == "Every" ? status : euid, "ls"))
                        msg += WHT "可寫\n";
                else
                        msg += HIR "禁止寫入\n";
                write(msg);
                return 1;
        }

        switch (para)
        {
        case "can_read":
        case "not_read":
                if (in_map(usr, dtr, dir))
                {
                        write("缺省配置中<可以讀取規則>中已經包含了對"
                              "該用戶(組)對目錄的訪問權限說明。\n");
                        break;
                }

                if (in_map(usr, der, dir))
                {
                        write("缺省配置中<禁止讀取規則>中已經包含了對"
                              "該用戶(組)對目錄的訪問權限說明。\n");
                        break;
                }

                if (para == "can_read")
                {
                        remove_from_map(usr, eer, dir);
                        etr = add_into_map(usr, etr, dir);
                } else
                {
                        remove_from_map(usr, etr, dir);
                        eer = add_into_map(usr, eer, dir);
                }

                SECURITY_D->set_security("extend_trusted_read", etr);
                SECURITY_D->set_security("extend_exclude_read", eer);
                reset_security();
                write("成功的修改了 " CYN + usr + NOR " 對目錄 " WHT + dir + NOR " 的讀取權限。\n");
                break;

        case "can_write":
        case "not_write":
                if (in_map(usr, dtw, dir))
                {
                        write("缺省配置中<可以寫入規則>中已經包含了對"
                              "該用戶(組)對目錄的訪問權限說明。\n");
                        return 1;
                }

                if (in_map(usr, dew, dir))
                {
                        write("缺省配置中<禁止寫入規則>中已經包含了對"
                              "該用戶(組)對目錄的訪問權限說明。\n");
                        return 1;
                }

                if (para == "can_write")
                {
                        remove_from_map(usr, eew, dir);
                        etw = add_into_map(usr, etw, dir);
                } else
                {
                        remove_from_map(usr, etw, dir);
                        eew = add_into_map(usr, eew, dir);
                }

                SECURITY_D->set_security("extend_trusted_write", etw);
                SECURITY_D->set_security("extend_exclude_write", eew);
                reset_security();
                write("成功的修改了 " CYN + usr + NOR " 對目錄 " WHT + dir + NOR " 的寫入權限。\n");
                break;

        case "unknow":
        case "none":
        case "inherit":
        case "default":

                flag  = remove_from_map(usr, etr, dir);
                flag |= remove_from_map(usr, eer, dir);
                flag |= remove_from_map(usr, etw, dir);
                flag |= remove_from_map(usr, eew, dir);
                if (! flag)
                {
                        write("原先沒有關于該用戶(組)對目錄的訪問權限設置。\n");
                        break;
                }

                SECURITY_D->set_security("extend_trusted_read", etr);
                SECURITY_D->set_security("extend_exclude_read", eer);
                SECURITY_D->set_security("extend_trusted_write", etw);
                SECURITY_D->set_security("extend_exclude_write", eew);
                reset_security();
                write("成功的取消了 " CYN + usr + NOR " 對目錄 " WHT + dir + NOR " 的訪問權限。\n");
                break;

        default:
                write ("權限參數必須為 can_read、not_read、can_write、"
                       "not_write、unknow 中的一種。\n");
                break;
        }

        return 1;
}

string title(string t)
{
        return "───────────── " + t +
               " ─────────────\n";
}

string auth_msg(mapping ruler, mapping default_ruler, string euid, string status)
{
        string *ks;
        string *arr;
        string msg;
        string line;
        int i, k;
        int l;

        msg = "";
        ks = sort_array(keys(ruler), (: strcmp($1, $2) :));
        for (i = 0; i < sizeof(ks); i++)
        {
                arr = ruler[ks[i]];
                if (! arrayp(arr) || ! sizeof(arr)) continue;
                line = 0;
                l = 0;
                for (k = 0; k < sizeof(arr); k++)
                {
                        if ((euid || status) &&
                            arr[k] != euid && arr[k] != status)
                                continue;

                        if (! line) line = sprintf(WHT "%-24s: ", ks[i]);
                        if (l >= 3)
                        {
                                l = 0;
                                line += "\n" + sprintf("%-24s  ", "");
                        }

                        if (default_ruler[ks[i]] &&
                            member_array(arr[k], default_ruler[ks[i]]) != -1)
                                line += CYN;
                        else
                                line += WHT;
                        line += sprintf("%-13s", arr[k]);
                        l++;
                }
                if (line) msg += line + "\n";
        }
        if (msg == "")
                msg = WHT "沒有限制。\n" NOR;
        else
                msg += NOR;
        return msg;
}

int in_map(string usr, mapping m, string index)
{
        string *arr;

        if (! m || ! arrayp(arr = m[index]))
                return 0;

        if (member_array(usr, arr) != -1)
                return 1;

        return 0;
}

int remove_from_map(string usr, mapping m, string index)
{
        string *arr;
        string *ks;
        int i;
        int flag;

        if (! m)
                return 0;

        if (! index)
        {
                // lookup the mapping
                ks = keys(m);
                flag = 0;
                for (i = 0; i < sizeof(ks); i++)
                        flag |= remove_from_map(usr, m, ks[i]);
                return flag;
        }

        if (! arrayp(arr = m[index]))
                return 0;

        if (member_array(usr, arr) == -1)
                return 0;

        arr -= ({ usr });
        if (! sizeof(arr))
                map_delete(m, index);
        else
                m[index] = arr;
        return 1;
}

mapping add_into_map(string usr, mapping m, string index)
{
        string *arr;

        if (! m)
                m = ([ index : ({ usr }) ]);
        else
        if (! arrayp(arr = m[index]))
                m += ([ index : ({ usr }) ]);
        else
        if (member_array(usr, arr) == -1)
        {
                arr += ({ usr });
                m[index] = arr;
        }

        return m;
}

void reset_security()
{
        SECURITY_D->save();
        SECURITY_D->reset_security();
}

int help(object me)
{
        write(@HELP
指令格式 : auth
           auth read | write
           auth <user> | <wizhood> -clear
           auth <user> | <wizhood> [ <directory> [ can_read | not_read | can_write | not_write | unknow ] ]

這個命令用來查詢或設置巫師的權限。 如果指明 read | write  表明查詢
讀取或是寫入的權限信息。

如果指定一個用戶或是組，表示查詢或是設置該用戶(組)的安全權限，如果
使用了參數 -clear 表示要清除該用戶或是組的的所有權限。如果指明了目
錄則設置該用戶(組)對目錄的訪問權限。其中 unknow 表示不針對該目錄進
行設置，即繼承上級目錄的權限。

注意：所有配置信息的修改均不能違反缺省配置，即如果缺省配置指明某個
用戶(組)不能或是可以訪問某個目錄，你不能再重新設置。當然，缺省配置
如果指明的是組，你可以對用戶在進行配置。比如：
缺省配置：(arch)不能訪問/backup/
你可以設置 test 用戶訪問/backup/

HELP
    );
    return 1;
}