// versiond.c

#include <runtime_config.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#define CONFIG_FILE     CONFIG_DIR "config"

// 配置文件中參數的格式是：  arg : value
// 如果以#打頭表示註釋，&打頭表示是系統註釋的。

void load_config();

void create()
{
        seteuid(getuid());
        load_config();
}

void load_config()
{
        string *tmp;
        string file;
        string line;
        string arg, value;
        string last_remember;
        string affix;
        int len;
        int sys_del;

        file = read_file(CONFIG_FILE);
        if (! stringp(file)) return;

        // 去掉"\r"保證和MSDOS的文件格式兼容
        file = replace_string(file, "\r", "");

        sys_del = 0;
        tmp = explode(file, "\n");
        foreach (line in tmp)
        {
                if (sys_del)
                {
                        // 上一個參數是被系統註釋掉的
                        last_remember = 0;
                        sys_del = 0;
                }

                // 去掉行首的空格
                while (strlen(line) && line[0] == ' ') line = line[1..<1];
                if (line[0] == '#')
                {
                        // 註釋
                        last_remember = line;
                        continue;
                }

                if (line[0] == '&')
                {
                        // 被系統註釋的
                        line = line[1..<1];
                        while (strlen(line) && line[0] == ' ') line = line[1..<1];
                        sys_del = 1;
                }

                // 去掉#以後所有的字符
                len = strsrch(line, '#');
                if (len != -1)
                {
                        // 記錄尾註
                        affix = line[len..<1];
                        line = line[0..len - 1];
                } else
                        affix = 0;

                if (! strlen(line))
                        continue;

                // 檢查該行
                if (sscanf(line, "%s:%s", arg, value) != 2)
                {
                        log_file("config", sprintf("syntax error: <%s>\n", line));
                        continue;
                }

                // 去掉arg末尾的空格
                while ((len = strlen(arg)) > 0 && arg[len - 1] == ' ')
                        arg = arg[0..<2];

                if (! strlen(arg))
                {
                        log_file("config", sprintf("syntax error: <%s>\n", line));
                        last_remember = 0;
                        continue;
                }

                // 去掉value打頭的空格
                while (strlen(value) && value[0] == ' ')
                        value = value[1..<1];

                // 去掉value末尾的空格
                while ((len = strlen(value)) > 0 && value[len - 1] == ' ')
                        value = value[0..<2];

                if (! sys_del)
                {
                        // 系統沒有註釋這個參數
                        set(arg, value);
                        sys_del = 0;
                }

                if (stringp(last_remember))
                {
                        // 如果有註釋，則加上
                        set_temp("remember/" + arg, last_remember);
                        last_remember = 0;
                }

                if (stringp(affix))
                {
                        // 如果有尾註，則加上
                        set_temp("affix/" + arg, affix);
                        affix = 0;
                }
        }
}

// 返回整數參數
int query_int(string index)
{
        mixed result;

        if (! intp(result = query(index)))
        {
                // 不是INT類型的值
                if (stringp(result))
                        // 是字符串嗎？如果是則取值
                        sscanf(result, "%d", result);
                else
                        result = 0;
                set(index, result);
        }

        return result;
}

// 返回字符串參數
string query_string(string index)
{
        string result;

        if (! stringp(result = query(index)))
                result = "unknow";

        return result;
}

// 返回參數的註釋
string query_remember(string index)
{
        return query_temp("remember/" + index);
}

// 返回參數的尾註
string query_affix(string index)
{
        return query_temp("affix/" + index);
}

// 返回配置文件的名字
string query_config_file_name() { return CONFIG_FILE; }