// config.c

#include <ansi.h>
#include <runtime_config.h>

inherit F_CLEAN_UP;

void write_config();
string trim(string str);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string key;
        mixed val;
        object ob;
        mapping dbase;
        string *cfg;
        string remember;
        string msg;
        string affix;
        int len;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg) arg = "";

        if (sscanf(arg, "-d %s", key) == 1)
        {
                key = trim(key);

                if( undefinedp(query(key, get_object(CONFIG_D))) )
                {
                        write("現在配置中沒有 " + key + " 這個參數。\n");
                        return 1;
                }

                delete(key, get_object(CONFIG_D));
                write("去掉了參數：" + key + "。\n");
                return 1;
        }

        if (sscanf(arg, "%s=%s", key, val) == 2)
        {
                // 去掉key/val兩端的空格
                key = trim(key);
                val = trim(val);

                if ((len = strsrch(val, '#')) != -1)
                {
                        // 有尾註
                        affix = val[len..<1];
                        val = val[0..len - 1];
                        val = trim(val);
                } else
                        affix = 0;

                // 去掉""
                sscanf(val, "\"%s\"", val);
                if (strlen(val) < 1)
                {
                        write("你沒有指明這個參數的值，如果需要刪除的話請用 -d 選項。\n");      
                        return 1;
                }

                if( !undefinedp(query(key, get_object(CONFIG_D))) && 
                    intp(query(key, get_object(CONFIG_D))) )
                        // 原先參數的值是整數
                        if (! sscanf(val, "%d", val))
                                write("注意：原先 " + key + " 使用的是整數值，現在類型變化了。\n");

                write(sprintf("重新設置了 %s 參數為 %O。\n", key, val));
                set(key, val, get_object(CONFIG_D));
                if (stringp(affix))
                        set_temp("affix/"+key, affix, get_object(CONFIG_D));

                return 1;
        }

        if (arg == "-w")
        {
                write_config();
                return 1;
        }

        if (arg == "-r")
        {
                // 重新讀取配置
                write("重新讀取運行中的配置參數。\n\n");
                if (objectp(ob = find_object(CONFIG_D)))
                {
                        destruct(ob);
                        call_other(CONFIG_D, "???");
                }
                return 1;
        }

        msg = "";
        msg += "Mud 名稱：\t\t" + get_config(__MUD_NAME__) + "\n"; 
        msg += "網路地址名稱伺服器埠號：" + get_config(__ADDR_SERVER_IP__) + "\n"; 
        msg += "Mudlib 路徑：\t\t" + get_config(__MUD_LIB_DIR__) + "\n"; 
        msg += "MudOS 執行檔路徑：\t" + get_config(__BIN_DIR__) + "\n\n"; 

        dbase = CONFIG_D->query_entire_dbase();
        if (! mapp(dbase))
        {
                write(msg + "現在沒有任何運行中的配置參數。\n");
                return 1;
        }

        msg += "現在系統的運行配置參數：\n";
        cfg = keys(dbase);
        cfg = filter_array(cfg, (: stringp($(dbase)[$1]) || intp($(dbase)[$1]) :));
        if (stringp(arg) && strlen(arg))
        {
                // 尋找匹配的參數
                cfg = filter_array(cfg, (: strsrch($1, $(arg)) != -1 :));
                if (! sizeof(cfg))
                {
                        write(msg + "現在沒有任何可以和 " + arg +
                              " 匹配的配置參數。\n");
                        return 1;
                }
        }

        cfg = sort_array(cfg, 1);
        foreach (key in cfg)
        {
                if (stringp(remember = CONFIG_D->query_remember(key)))
                        msg += CYN + remember + NOR "\n";
                if (! stringp(affix = CONFIG_D->query_affix(key)))
                        affix = "";
                msg += sprintf("%-20s: " WHT "%-25O" NOR "%-15s\n",
                               key, dbase[key], CYN + affix + NOR);
        }
        msg += NOR;

        write(msg);
        return 1;
}

// 寫回參數
void write_config()
{
        string *tmp;
        string file;
        string line;
        string arg, value;
        string affix;
        mapping dbase;
        string *cfg;
        int len;
        int i;

        // 取當前所有的參數
        if (! mapp(dbase = CONFIG_D->query_entire_dbase()))
                dbase = ([ ]);
        cfg = keys(dbase);
        cfg = filter_array(cfg, (: stringp($(dbase)[$1]) || intp($(dbase)[$1]) :));

        // 讀取配置文件
        file = read_file(CONFIG_D->query_config_file_name());
        if (! stringp(file))
                file = "";

        // 去掉"\r"保證和MSDOS的文件格式兼容
        file = replace_string(file, "\r", "");

        tmp = explode(file, "\n");

        // 去掉最後的空行
        while (sizeof(tmp) && tmp[sizeof(tmp) - 1] == "")
                tmp = tmp[0..<2];

        for (i = 0; i < sizeof(tmp); i++)
        {
                line = tmp[i];

                // 去掉行首的空格
                while (strlen(line) && line[0] == ' ') line = line[1..<1];
                if (line[0] == '#')
                        continue;

                if (line[0] == '&')
                {
                        // 被系統註釋的
                        line = line[1..<1];
                        while (strlen(line) && line[0] == ' ') line = line[1..<1];
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
                        continue;

                // 去掉arg末尾的空格
                while ((len = strlen(arg)) > 0 && arg[len - 1] == ' ')
                        arg = arg[0..<2];

                // 更換該行
                value = dbase[arg];

                if (stringp(value))
                        line = sprintf("%s : %s", arg, value);
                else
                if (undefinedp(value) || ! intp(value))
                        line = "& " + line;
                else
                        line = sprintf("%s : %d", arg, value);

                cfg -= ({ arg });

                // 加上尾註
                if (stringp(affix))
                        line = sprintf("%-44s %s", line, affix);

                tmp[i] = line;
        }

        tmp += ({ "" });
        foreach (arg in cfg)
        {
                value = dbase[arg];

                if (stringp(value))
                        line = sprintf("%s : %s", arg, value);
                else
                if (intp(value))
                        line = sprintf("%s : %d", arg, value);
                else
                        continue;
                tmp += ({ line });
        }

        file = implode(tmp, "\n") + "\n";
        write_file(CONFIG_D->query_config_file_name(), file, 1);
        write("將參數寫回到配置文件中。\n");
}

// 去掉str兩端的空格
string trim(string str)
{
        int len;

        // 去掉str兩端的空格
        while (str[0] == ' ') str = str[1..<1];
        while ((len = strlen(str) - 1) >= 0 && str[len] == ' ')
                str = str[0..<2];

        return str;
}

int help(object me)
{
        write(@HELP
指令格式 : config [-r | -w] | [<配置項>=<值>] | [-d <配置項>]

Show 出本 MUD 的 Startup Configuration 。如果不加參數則同時
顯示出運行中的配置(/adm/etc/config)。

-r 可以重新讀取運行中的配置。
-w 可以重新寫入運行中的配置。
-d 可以去掉一個配置項。

HELP );
        return 1;
}
