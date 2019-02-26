// ban.c
//
#include <ansi.h>

#define BANNED_SITES    "/adm/etc/banned_sites"
#define WELCOME         "/adm/etc/welcome_sites"
#define BANNED_IDS      "/adm/etc/banned_ids"
#define BANNED_NAMES    "/adm/etc/banned_names"

void load_sites();
void load_welcome();
void load_banned_names();
void load_banned_ids();

void add_site(string pattern);                  // ban 一個不歡迎的 ip 地址
void remove_site(string pattern);               // 解封一個 ip 地址
void add_welcome_user(string user_id);          // 增加一個 welcome 用户(id)
void remove_welcome_user(string user_id);       // 刪除一個 welcome 用户(id)
void remove_netclub(string netline);            // 移去一條網吧線
void open_club_line(object user);               // 由 welcome 用户自己打開網吧地址

// 屬於 welcome 的用户不受 ban 的影響，而且可以開放這根線上多個 ip 地址
string list_welcome_users();                    // welcome users列表
string list_sites();                            // 被 ban 的 ip 列表

int is_banned(string site);                     // 判斷是否一個 ban 的 ip (logind.c調用)
int is_netclub(string netline);                 // 判斷是否一個網吧線的用户(logind.c調用)
int is_welcome(string user_id);                 // 判斷是否一個 welcome 的用户(logind.c調用)

string *Sites;
string *Netclubs;
string *Welcomes;
string *Banned_IDs;                             //  ban id 表
string *Banned_Names;                           //  ban 中文名錶

void create()
{
        seteuid(getuid());
        Netclubs = ({"127.0.0.1",});
        load_sites();
        load_welcome();
}

string *query_sites() { return Sites; }
string *query_welcomes() { return Welcomes; }
string *query_banned_ids() { return Banned_IDs; }
string *query_banned_names() { return Banned_Names; }


void load_banned_ids()
{
        string *tmp;
        string file;
        int loop;
        Banned_IDs = ({});

        if (file_size(BANNED_IDS) < 0)
                return;

        file = read_file(BANNED_IDS);
        if (! file) return;

        tmp = explode(file, "\n");
        for (loop = 0; loop < sizeof(tmp); loop++)
                if (tmp[loop][0] == '#' || tmp[loop][0] == '\n' || tmp[loop] == "")
                        continue;
                else    Banned_IDs += ({ tmp[loop] });
}

void load_banned_names()
{
        string *tmp;
        string file;
        int loop;
        Banned_Names = ({});

        if (file_size(BANNED_NAMES) < 0)
                return;

        // reads in the list of the sites
        file = read_file(BANNED_NAMES);
        if (!file) return;

        tmp = explode(file, "\n");
        for (loop = 0; loop < sizeof(tmp); loop++)
                if (tmp[loop][0] == '#' || tmp[loop][0] == '\n' || tmp[loop] == "")
                        continue;
                else    Banned_Names += ({ tmp[loop] });
}

void load_sites()
{
        string *tmp;
        string file;
        int loop;
        Sites = ({});

        if (file_size(BANNED_SITES) < 0)
                return;

        // reads in the list of the banned sites
        file = read_file(BANNED_SITES);
        if (! file) return;

        tmp = explode(file, "\n");
        if (! sizeof(tmp)) return;
        for (loop = 0; loop < sizeof(tmp); loop++)
                if (! sizeof(tmp[loop]) || tmp[loop] == "" ||
                    tmp[loop][0] == '#' || tmp[loop][0] == '\n')
                        continue;
                else    Sites += ({ tmp[loop] });
}

void load_welcome()
{
        string *tmp;
        string file;
        int loop;
        Welcomes = ({});

        if (file_size(WELCOME) < 0)
                return;

        // reads in the list of the banned sites
        file = read_file(WELCOME);
        if (! file) return;

        tmp = explode(file, "\n");
        if (! sizeof(tmp)) return;
        for (loop = 0; loop < sizeof(tmp); loop++)
                if (! sizeof(tmp[loop]) || tmp[loop] == "" ||
                    tmp[loop][0] == '#' || tmp[loop][0] == '\n')
                        continue;
                else    Welcomes += ({ tmp[loop] });
}

int is_multi_login(string site)
{
        object *usr;
        int i,ip_count,max_multilogin;


        max_multilogin = is_netclub(site) ? 12 : 4;

        usr = children(USER_OB);
        for( i = sizeof(usr)-1,ip_count = 0; i >=0; i-- )
                if( site == query_ip_number(usr[i]))
                        ip_count ++;

        if( ip_count >= max_multilogin )
                return 0;
        return 1;
}

int is_banned(string site)
{
        string *line = ({site});
        string tmp1, tmp2, tmp3, tmp4;
        int i;

        if (! site)  return 1;

        if (sscanf(site, "%s.%s.%s.%s", tmp1, tmp2, tmp3, tmp4) != 4)
                return 1;

        /*
        // 禁止使用虛擬 ip 或 route
        if (tmp4 == "0" || tmp4 == "255")
                return 1;
        */
        if (! sizeof(Sites))
                return 0;

        for (i = 0; i < sizeof(Sites); i++)
                if (sizeof(regexp(line, Sites[i])) == 1)
                        return 1;
        return 0;
}
void add_site(string site)
{
        string tmp1, tmp2, tmp3, tmp4;
        int i;

        if (! site)  return;

        // 禁止地址
        if (sscanf(site, "%s.%s.%s.%s", tmp1, tmp2, tmp3, tmp4) == 4)
        {
                if (is_banned(site))
                {
                        write (RED + site + "已經被禁止!\n" NOR);
                        return;
                }
                if (tmp1 == "*")
                {
                        write (RED + site + "的 IP 範圍太大了!\n" NOR);
                        return;
                }
                Sites += ({site});
                write_file(BANNED_SITES, Sites[sizeof(Sites)-1] + "\n", 0);
                write (RED "\n禁止地址" + site + "...OK！\n" NOR);
                Netclubs -= ({ site });
                return;
        }

        // 禁止使用中文名
        if (is_chinese(site))
        {
                if (member_array(site, Banned_Names) != -1)
                {
                        write (RED + site + "已經被禁止！\n" NOR);
                        return;
                }
                for (i = 0; i < sizeof(Banned_Names); i++)
                if (strsrch(site, Banned_Names[i]) != -1)
                {
                        write (RED + site + "已經被禁止！\n" NOR);
                        return;
                }
                Banned_Names+= ({site});
                write_file(BANNED_NAMES, Banned_Names[sizeof(Banned_Names)-1] + "\n", 0);
                write (RED "\n禁止使用中文名" + site + "...OK！\n" NOR);
                return;
        }

        i = strlen(site);
        if ((strlen(site) < 3) || (strlen(site) > 12))
        {
                write("英文名字必須是 3 到 12 個英文字母。\n");
                return;
        }
        while (i--)
        if (site[i] < 'a' || site[i] > 'z')
        {
                write("只能用英文字母。\n");
                return;
        }
        if (member_array(site, Banned_IDs) != -1)
        {
                write(site + "在列表中已經存在。\n");
                return;
        }

        Banned_IDs += ({ site });
        write_file(BANNED_IDS, Banned_IDs[sizeof(Banned_IDs)-1] + "\n", 0);
        write (BOLD "\n增加" + HIY + site + HIW + "到列表...OK！\n" NOR);
}


void remove_site(string site)
{
        string tmp1, tmp2, tmp3, tmp4;
        int i;
        string *line = ({site});

        if (! site)  return;

        // 解除禁止地址
        if (sscanf(site, "%s.%s.%s.%s", tmp1, tmp2, tmp3, tmp4) == 4)
        {
                if (! is_banned(site))
                {
                        write ("\n這個地址並未被禁止!\n");
                        return;
                }
                for (i = 0; i < sizeof(Sites); i++)
                if (sizeof(regexp(line, Sites[i])) == 1)
                        Sites -= ({ Sites[i] });
                write_file(BANNED_SITES, implode(Sites, "\n") + "\n", 1);
                write (BOLD "\n解禁地址" + site + "...OK！\n" NOR);
                return;
        }

        // 解除禁止使用的中文名
        if (is_chinese(site))
        {
                if (member_array(site, Banned_Names) == -1)
                {
                        write (RED + site + "沒被禁止使用!\n" NOR);
                } else
                {
                        Banned_Names-= ({site});
                        write_file(BANNED_NAMES, implode(Banned_Names, "\n") + "\n", 1);
                        write (RED "\n解禁中文名" + site + "...OK！\n" NOR);
                        return;
                }
                for (i = 0; i < sizeof(Banned_Names); i++)
                if (strsrch(site, Banned_Names[i]) != -1)
                {
                        Banned_Names -= ({site});
                        write_file(BANNED_NAMES, implode(Banned_Names, "\n") + "\n", 1);
                        write (RED "\n解禁中文名" + site + "...OK！\n" NOR);
                        return;
                }
                write (HIY + site + HIW + "沒被禁止！\n" NOR);
                return;
        }
        i = strlen(site);
        if ((strlen(site) < 3) || (strlen(site) > 12))
        {
                write("英文名字必須是 3 到 12 個英文字母。\n");
                return;
        }
        while(i--)
        if (site[i] < 'a' || site[i] > 'z')
        {
                write("只能用英文字母。\n");
                return;
        }
        if (member_array(site, Banned_IDs) != -1)
        {
                Banned_IDs -= ({ site });
                write_file(BANNED_IDS, implode(Banned_IDs, "\n") + "\n", 1);
                write (BOLD "\n解除使用英文名" + HIY + site + HIW + "的限制!\n" NOR);
                return;
        }
        write (HIY + site + HIW + "沒被禁止!\n" NOR);
}




int is_welcome(string user_id)
{
        if (! sizeof(Welcomes))
                return 0;

        if (member_array(user_id, Welcomes) == -1)
                return 0;
        return 1;
}

void add_welcome_user(string user_id)
{
        if (is_welcome(user_id))
        {
                write("這個 id 已經列入了 welcome player ！\n");
                return;
        }
        Welcomes += ({ user_id });
        write_file(WELCOME, Welcomes[sizeof(Welcomes)-1] + "\n", 0);
        /*
        write (BOLD "\n增加 welcome user " + HIY + user_id + HIW + "...OK！\n" NOR);
        write (list_welcome_users());
        */
}

void remove_welcome_user(string user_id)
{
        if (! is_welcome(user_id))
        {
                write("這個 id 並未列入了 welcome player ！\n");
                return;
        }
        Welcomes -= ({ user_id });
        write_file(WELCOME, implode(Welcomes,"\n") + "\n", 1);
        write (BOLD "\n刪除 welcome user " + HIY + user_id + HIW + "...OK！\n" NOR);
        write (list_welcome_users());
}

string list_welcome_users()
{
        if (! sizeof(Welcomes))
                return (BOLD "現在還沒有 Welcome user 。\n" NOR);
        return sprintf(HIY + MUD_NAME + "的 Welcome users 如下：\n" +
                       HIC + "  %s\n" NOR, implode(Welcomes, "\n  "));
}

void list_netclubs()
{
        if (! sizeof(Netclubs))
        {
                write(BOLD "現在沒有開放的網吧地址!\n" NOR);
                return;
        }
        printf(HIY "\n現在允許多人同時進入" + MUD_NAME + "的ip地址如下：\n" +
               HIC + "  %s\n" NOR, implode(Netclubs, "\n  "));
}

int is_netclub(string netline)
{
        int i;
        string *line = ({netline});

        if (! sizeof(Netclubs))
                return 0;

        for (i = 0; i < sizeof(Netclubs); i++)
        {
        if (! Netclubs[i]) continue;
        if (sizeof(regexp(line, Netclubs[i])) == 1)
                return 1;
        }
        return 0;
}

void remove_netclub(string netline)
{
        int i;
        string *line = ({netline});

        for (i = 0; i < sizeof(Netclubs); i++)
        if (sizeof(regexp(line, Netclubs[i])) == 1)
        {
                Netclubs -= ({ Netclubs[i] });
                write (HIR "\n刪除網吧地址" + netline + "...OK！\n" NOR);
                return;
        }
        write ("\n這個地址並不是網吧線!\n");
}

void open_club_line(object user)
{
        int i;
        string netline;
        string *line;

        if (! user) user = this_player();
        netline = query_ip_number(user);
        line = ({netline});

#ifdef DB_SAVE
        if (! wizardp(user) && ! MEMBER_D->is_valid_member(query("id", user)))
#else
        if (! wizardp(user) && ! is_welcome(query("id", user)))
#endif
        {
                write("你未列入 welcome player ，請向巫師申請！\n");
                write("\n申請方式：通過msg mail寫信給arch以上級別的巫師，通過後\n"
                      "巫師會回信通知你,以後用這個 id 上來打開你的網吧線即可，\n"
                      "請注意督促你所在網吧的玩家遵守遊戲規則。謝謝合作！\n\n");
                return;
        }
        for (i = 0; i < sizeof(Netclubs); i++)
        if (Netclubs[i] && sizeof(regexp(line, Netclubs[i])) == 1)
        {
                write (HIY + netline + "網吧線已經打開！\n" NOR);
                return;
        }
        if (netline == "127.0.0.1")
        {
                write (HIY "你現在所佔用的是網關！\n" NOR);
                remove_welcome_user(query("id", user));
                return;
        }
        Netclubs += ({ netline });
        write (BOLD "\n打開網吧地址" + netline + "...OK！\n" NOR);
}
string list_sites()
{
        int flag;
        string msg = HIC "\n現在被禁止進入" + MUD_NAME + "的 ip 地址如下：\n" + HIR;

        if (! sizeof(Sites))
                return (BOLD "現在沒有被禁止的地址！\n" NOR);
        flag = 0;
        foreach (string str in sort_array(Sites, 1))
        {
                msg += str;
                flag++;
                if (flag % 8)
                        msg += "\t";
                else
                        msg += "\n";
        }
        return msg + "\n" + NOR;
}

int vaild_allow_address(object ob)
{
        string *address;
        string *line;
        int i;

        if (! ob) return 0;

        address=query("allow_ip", ob);
        if (! sizeof(address))
        {
                set_temp("no_allow_ip", 1, ob);
                // write(HIY "\n警告：你未設定自己的登錄地址範圍。請用 allowip 指令設置。\n" NOR);
                if (is_welcome(query("id", ob)) && ! is_netclub(query_ip_number(ob)))
                {
                        open_club_line(ob);    // 並自動開放網吧限制
                        log_file("static/open_netclub",
                                 sprintf("user %s open ip address %s limit in %s.\n",
                                         query("id", ob),query_ip_number(ob),ctime(time())));
                }
                return 1;
        }
        line = ({query_ip_number(ob)});
        for (i = 0; i < sizeof(address); i++)
        if (sizeof(regexp(line, address[i])) == 1)
        {
                if( is_welcome(query("id", ob)) && !is_netclub(query_ip_number(ob)) )
                {
                        open_club_line(ob);    // 並自動開放網吧限制
                        log_file("static/open_netclub",
                                 sprintf("user %s open ip address %s limit in %s.\n",
                                         query("id", ob),query_ip_number(ob),ctime(time())));
                }
                return 1;
        }
        write(HIR "\n嚴重警告：你不在自己所設定的登錄地址範圍內。\n" NOR);
        log_file("static/ALLOW_IP", sprintf("%s(%s)於%s試圖從%s登錄。\n",
                 query("name", ob),query("id", ob),ctime(time()),query_ip_number(ob)));
        return 0;
}