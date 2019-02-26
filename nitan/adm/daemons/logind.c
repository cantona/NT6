// This program is a part of NITAN MudLIB
// logind.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>

#define WAITING_ENTER_TIME      3
#define MULTI_LOGIN             30
#define PUBLIC_IP               "127.0.0.1"

#define MUDLIST_CMD             "/cmds/usr/mudlist"
#define REBOOT_CMD              "/cmds/arch/reboot"
#define MSG_CMD                 "/cmds/usr/msg"
#define FESTIVAL_CMD            "/cmds/usr/festival"
#define INVENTORY_CMD           "/cmds/usr/inventory"

#define NO_FEE_WARNING  "$$【注意】為節約系統資源，如果玩家在 " + UNLOG_IDLE + " 天之內沒有任何活動記錄，人物將被系統自動清除。$$"

inherit F_DBASE;

#include "/adm/etc/database.h"

nosave int wiz_lock_level = WIZ_LOCK_LEVEL;
nosave int cruise_lock = 0;
nosave int mad_lock = 0;
nosave mapping blocks = ([]);

nosave string *banned_name = ({
        "你", "你的", "我","我的","自己","屁", "他", "他的","她", "她的","它", "它的",
        "鬼王","風雲","流氓","爸","媽","祖先","祖宗","爺","奶","張春龍","毛澤東","鄧小平","江澤民",
        "胡錦濤", "【","】","馬克思","恩格斯","列寧","抄","手淫","老百姓","臨時人物","女馬","大便",
});

nosave string *banned_id = ({
        "domain", "root", "mudlib", "quit",
        "arch", "wizard", "apprentice",
        "immortal", "player", "fuck", "admin",
        "all", "none", "cancel", "leave", "out",
        "entry", "enter", "shit", "tmd", "tnnd",
        "lonely",
});

protected void get_id(string arg, object ob);
protected void confirm_cruiseid(string yn, object ob);
protected void get_cruisepwd(string pass, object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
protected void init_new_player(object user);
protected void check_ok(object ob);
void waiting_enter_world(object ob, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string name, int maxlen);
int block_ip(string ip, int time, string reason);
int unblock_ip(string ip);

string resolve_ip_number(string ip_number)
{
        string part, *parts;
        string full;

        if( !ip_number ) return "127000000001";
        parts = explode(ip_number, ".");
        full = "";
        foreach (part in parts)
                full += replace_string(sprintf("%3s", part), " ", "0");
        return full;
}

void destruct_ob(object me)
{
        destruct(me);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "連線精靈");
        if( intp(WIZ_LOCK_LEVEL) )
                wiz_lock_level = WIZ_LOCK_LEVEL;
        else
                wiz_lock_level = 0;
}

void waiting_login(object ob, string arg)
{
        write("載入中，請稍後 ...\n");
        input_to( (: waiting_login, ob :) );
}

void logon(object ob)
{
        mapping tmp_time;
        object *usr, *login_usr;
        string str, ip_num;
        string *ips, *vips, *args1, *args2;
        int now_time;
        int i, wiz_cnt, ppl_cnt, ip_cnt, ban_cnt, login_cnt;
        int reg_usr, max_usr, max_ips, time1, time2;

        if( !SYSTEM_D->valid_login() ) {
                write(HIY + MUD_FULL_NAME + "載入中，請稍後 ...\n" NOR);
                SYSTEM_D->add_loginuser( ob );
                input_to((: waiting_login, ob :));
                return;
        }

        str = query_ip_number(ob);
        now_time = time() & 0xFFFFFFFE;
        if( mapp(tmp_time = blocks[str]) ) {
                if( now_time - tmp_time["time"] < tmp_time["punish"] ) {
                        write(tmp_time["reason"] + "請過" +
                              appromix_time(tmp_time["time"] + tmp_time["punish"] - now_time) + "再嘗試連線。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                unblock_ip(str);
        }

        login_usr = filter_array(children(LOGIN_OB), (: query_ip_number($1) == $2 :), str);
        if( (sizeof(login_usr) > 30 && str != PUBLIC_IP) ) {
                block_ip(str, 300, "您的IP產生了大量廢棄連接！");
                /*
                for (i = 0; i < sizeof(login_usr); i ++)
                        destruct(login_usr[i]);
                */
                call_out("destruct_ob", 0, ob);
                return;
        }

        write(ESC "[2J");
        write(color_filter(read_file(WELCOME)));

        //catch(MUDLIST_CMD->main());
        UPTIME_CMD->main();
        if( query_temp("tomud", ob) )
                write(ALERT("經典文字MUD遊戲『王者之戰』，群號『46899981』，本遊戲為免費遊戲！$$" +
                        "請到 http://mudbuilder.com 瀏覽本遊戲主頁和論壇、新聞。$$"+
                        "如果有任何疑問，請到本遊戲論壇專區提問，或聯系QQ 150867 咨詢。$$"));


        if( BAN_D->is_banned(str) == 1 ) {
                write(HIR "你的地址在本 MUD 不受歡迎，請去論壇 muds.cn 申述。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( mad_lock == 1 ) {
                write("現在時空已經封閉了，不能進入！！ \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        /*if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) )
                write(HIY "現在本站正在同步版本，如果你不是巫師，請稍候再登錄。\n\n" NOR);
        else*/ if( REBOOT_CMD->is_rebooting())
                write(HIY "現在本站正在準備重新啟動，如果你不是巫師，請稍候再登錄。\n\n" NOR);

        usr = users() + filter(children(LOGIN_OB), (: interactive :));
        ip_cnt  = 0;
        wiz_cnt = 0;
        ppl_cnt = 0;
        ban_cnt = 0;
        login_cnt = 0;
        ips  = ({});
        vips = ({});

        reg_usr = DATABASE_D->db_count_user(); 
        args1 = explode(read_file(CONFIG_DIR + "max_online", 1), ":");
        args2 = explode(read_file(CONFIG_DIR + "max_ips", 1), ":");
        time1 = to_int(args1[1]);
        time2 = to_int(args2[1]);
        max_usr = to_int(args1[0]);
        max_ips = to_int(args2[0]);

        for( i=0;i<sizeof(usr);i++ ) {
                ip_num = query_ip_number(usr[i]);
                if( str == ip_num ) {
                        ip_cnt++;
                        if( !environment(usr[i]) ) ban_cnt++;
                }
                if( usr[i]->is_vip() && member_array(ip_num, vips) == -1 ) vips += ({ ip_num });
                if( member_array(ip_num, ips) == -1 ) ips += ({ ip_num });
                if( base_name(usr[i]) == LOGIN_OB ) login_cnt++;
                else if( wizardp(usr[i]) ) {
                        if( !query("env/invisible", usr[i]) ) wiz_cnt++;
                }
                else ppl_cnt++;
        }

        //write(sprintf("目前注冊玩家" HIW "%d" NOR "位，最高在線人數" HIC "%d" NOR "人(" CYN "%s" NOR ")，最高在線IP數" HIY "%d" NOR "個(" CYN "%s" NOR ")\n" NOR,
                //reg_usr, max_usr, TIME_D->replace_ctime(time1), max_ips, TIME_D->replace_ctime(time2)));
        write(sprintf("目前注冊玩家" HIC "%s" NOR "位，最高同時在線人數" HIW "%s" NOR "人(" CYN "%s" NOR ")\n" NOR,
                chinese_number(reg_usr), chinese_number(max_usr), TIME_D->replace_ctime(time1)));

        write(sprintf("目前共有 " HIY "%d" NOR " 位神仙、" HIW "%d" NOR " 位江湖人士在江湖中，以及 " HIB "%d" NOR " 位朋友正在步入江湖的途中。"+ ((wiz_lock_level>0)?HIR"(禁止玩家登入)":HIC"(允許玩家登入)") + "\n\n" NOR,
                   (wiz_cnt), (ppl_cnt), (login_cnt) ));

        if( ppl_cnt > max_usr )
                write_file(CONFIG_DIR "max_online", sprintf("%d:%d", ppl_cnt, time()), 1);

        if( sizeof(ips) > max_ips )
                write_file(CONFIG_DIR "max_ips", sprintf("%d:%d", sizeof(ips), time()), 1);

        if( ban_cnt > 10 ) {
                write("這個IP上同時正在連線的玩家太多了，請稍候再嘗試！！ \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( ip_cnt > MULTI_LOGIN && str != PUBLIC_IP && !BAN_D->is_netclub(str) ) {
                write("對不起，" + MUD_NAME + "限制相同ip多重登錄。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        //query_ip_port(ob) == TOMUD
        if( query_temp("tomud", ob)){
                write(CLEAN0);
                write(CLEAN1);
                write(CLEAN2);
                write(TMI("version"));
                input_to("get_version", ob);
        }

#if 0
        if( !query_temp("big5", ob)){
                write(HIC "□□□□才棟□虜砰□叫塊□GB/BIG5□跑□才棟□□□鋇□魁□□□\n" NOR
                      "目前的字符集是簡體，請輸入GB/BIG5改變字符集，或直接登錄用戶。\n"
                      "請輸入您的英文名字(" CYN "忘記密碼請輸入「pass」" NOR ")：\n");
        } else {
                delete_temp("big5", ob);
                write(HIC "目前的字符集是繁體，請輸入GB/BIG5改變字符集，或直接登錄用戶。\n" NOR);
                set_temp("big5", 1, ob);
                write("目前的字符集是繁體，請輸入GB/BIG5改變字符集，或直接登錄用戶。\n");
                write("請輸入您的英文名字(" CYN "忘記密碼請輸入「pass」" NOR ")：\n");
        }
#else
	write("請輸入您的英文名字(" CYN "忘記密碼請輸入「pass」" NOR ")：\n");
#endif
        input_to( (: get_id :), ob );
}

protected void get_version(string arg, object ob)
{
        if( !arg || arg[0..3] != CURRENT_CLIENT_VERSION ) {
                write(HIY "請從下列地址下載Tomud客戶端\n" NOR);
                write(HIG "    http://www.mudbuilder.com/download/tomudsetup.exe\n" NOR);
                write(HIY "或使用Zmud客戶端選擇3000端口重新連接。\n\n" NOR);
                //call_out("destruct_ob", 0, ob);
                //return;
        }
        input_to( (: get_id :), ob );
}

protected void pass_id(string arg, object ob)
{
        mixed  res;
        int    flag;
        string where;

        write("該服務尚未啟用。\n");
        call_out("destruct_ob", 0, ob);
        return;

        if( wiz_level(arg) ) {
                write("巫師ID密碼則必須親自找天神修改密碼。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( set("id",arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag)
        {
                if( (int)res[0] == 3)
                {
                        write(sprintf("[%s] 這個 ID 目前正在漫遊中，請稍後再試。。\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[1];
                if( stringp(where) && where != LOCAL_STATION)
                {
                        write(sprintf("[%s] 這個 ID 數據目前在%s，你還是去那裡找回密碼吧。\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( !flag ) {
                write("本遊戲沒有 " + arg + " 這位玩家。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( !ob->restore() ) {
                write("該角色儲存擋出了一些問題，請利用 guest 人物通知巫師處理。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        write("請輸入該角色的信箱地置(email)：\n");
        input_to("get_email", 1, ob);
        return;
}

protected void get_email(string arg, object ob)
{
        string pass, msg;
        object user;

        user = make_body(ob);
        if( !user || !user->restore() ) {
                write("該角色儲存擋出了一些問題，請利用 guest 人物通知巫師處理。\n");
                if( user) call_out("destruct_ob", 0, user);
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( query("email", user) == arg){
                write("系統已將新管理密碼 Email 至您的信箱。\n");
                pass = SMTP_D->random_passwd(8);
#ifdef ENABLE_MD5_PASSWORD
                set("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
                set("ad_password", crypt(pass,0), ob);
#endif
                ob->save();

                msg = @LONG
Hello, %id.

感謝您參與網絡遊戲%MUD_NAME，您所使用的賬號(%id)的管理密碼現
已經被系統修改成為%passwd，下次登錄的時候請您使用新的管理密碼
登錄，並重新設置登錄使用的普通密碼。對此造成的不便敬請原諒。

                             %data
LONG ;
                msg = replace_string(msg, "%id", query("id", ob));
                msg = replace_string(msg, "%MUD_NAME", MUD_NAME);
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));

                //MAIL_D->queue_mail(0, 0, arg, "王者之戰 - " + query("id", ob) + " 角色密碼", msg);
                SMTP_D->send_passmail(0, 0, arg, "王者之戰 - " + query("id", ob) + " 角色密碼", msg);
        } else
                write("您輸入的資料與該角色不符。\n");

        call_out("destruct_ob", 0, user);
        call_out("destruct_ob", 0, ob);
        return;
}

protected void get_id(string arg, object ob)
{
        object *usr;
        string where, ip;
        mixed  res;
        int    i, flag;

        arg = lower_case(arg);

#if 0
        if( arg == "big5" ) {
                set_temp("big5", 1, ob);
                logon(ob);
                return;
        } else if( arg == "gb" ) {
                delete_temp("big5", ob);
                logon(ob);
                return;
        } else if( arg == "pass" ) {
                write("請輸入您的英文ID：\n");
                input_to("pass_id", ob);
                return;
        }
#else
	if ( arg == "pass" ) {
		write("請輸入您的英文ID：\n");
		input_to("pass_id", ob);
		return;
	}
#endif

#if 0
        if( arg == "lonely" )
        {
                write("就憑你也敢偷巫師的帳號？\n");
                destruct(ob);
                return;
        }

        if( arg == "lonely21" ) arg = "lonely";
#endif

        if( !check_legal_id(arg) ) {
                /*
                addn_temp("fake_id", 1, ob);
                if( query_temp("fake_id", ob)>20 &&
                    (ip = query_ip_number(ob)) != PUBLIC_IP ) {
                        block_ip(ip, 300, "您的IP持續登錄無效ID！");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                */
                write(YEL "請輸入您的英文名字：" NOR);
                input_to("get_id", ob);
                return;
        }

        if( intp(MAX_USERS) && MAX_USERS > 0 ) {
                if( (string)SECURITY_D->get_status(arg) == "(player)" &&
                    sizeof(users()) >= MAX_USERS ) {
                        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                        if( !find_body(arg) ) {
                                write("對不起，" + MUD_NAME +
                                      "的使用者已經太多了，請待會再來。\n");
                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                }
        }

        if( wiz_level(arg) < 1 ) {
                /*
                if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) ){
                        write("現在本站正在同步版本中，暫時不能登錄，請稍候再嘗試。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                } else
                */
                if( REBOOT_CMD->is_rebooting() && !find_body(arg) ) {
                        write("現在本站正準備重新啟動，暫時不能登錄，請稍候再嘗試。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }

        if( wiz_level(arg) < wiz_lock_level ) {
                write("對不起，" + MUD_NAME + "目前限制巫師等級 " + WIZ_LOCK_LEVEL + " 以上的人才能連線。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( AHACK_D->query_block(arg) ) {
                write(HIY "這個賬號被暫時封鎖了，請用 guest 人物登入與在線巫師聯系。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( set("id", arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( arg == "guest" ) {
                object user;
/*
                user = find_body("guest");
                if( user ) {
                        write("目前 guest 賬號已有人在使用，請等一下再登陸。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
*/

                set("body", USER_OB, ob);
                if( !objectp(user = make_body(ob)) ) {
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                set("name", "臨時人物", user);
                set("gender", "男性", user);
                set("title", "普通百姓", user);
                set("food", 500, user);
                set("water", 500, user);
                //set("channels", ({"new","chat","rumor","sos","info"}), user);
                set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
                CHANNEL_D->register_channel(user, query("channels")); 
                set("str", 20, user);
                set("int", 20, user);
                set("cor", 20, user);
                set("con", 20, user);
                set("per", 20, user);
                set("kar", 20, user);
                waiting_enter_world(ob,user);
                return;
        }

#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, on_time, fee_time,
                                  last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag ) {
                if( (int)res[0] == 3 ) {
                        write(sprintf("[%s] 這個 ID 目前正在漫遊中，請稍後再嘗試登陸。。\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[3];
                if( wiz_level(arg) < 1 && stringp(where) && where != LOCAL_STATION ) {
                        if( (int)res[0] > 0 ) {
                                if( (int)res[0] == 2 )
                                        write(sprintf("[%s] 這個 ID 目前正在%s閉關，如想漫遊，請先將該 ID 從%s站退出。\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站",
                                                      ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                                else if( (int)res[0] == 1 )
                                        write(sprintf("[%s] 這個 ID 目前正在%s連線，如想漫遊，請先將該 ID 從%s站退出。\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站",
                                                      ! undefinedp(stations[where]) ? stations[where] : "其他站"));

                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                        write(sprintf("[%s] 這個 ID 數據目前在%s，你想將該 ID 數據漫遊過來(y/n)？：\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "其他站"));
                        write("如果該 ID 不是你注冊的或者你不想漫遊，請輸入(n/N)來重新注冊或登陸其他 ID。\n" NOR);
                                input_to("confirm_cruiseid", 1, ob);
                        return;
                }
                set_temp("res", res, ob);
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( flag ) {
                if( ob->restore() ) {
                        if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" ) {
                                if( query("wizpwd", ob)){
                                        write("請輸入巫師專用密碼：\n");
                                        input_to("get_wizpwd", 1, ob);
                                        return;
                                }

                                write("\n警告！您沒有設置巫師專用密碼！請登陸後用" HIW " wizpwd " NOR "命令設置。\n");
                                write("請輸入密碼：\n");
                                input_to("get_passwd", 1, ob);
                                return;
                        }
                        write("這個角色已經存在，請輸入該角色的密碼：\n");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物儲存擋出了一些問題，請利用 guest 人物通知巫師處理。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() ) {
                write("對不起，由于連接不上數據庫所在服務器，目前" + MUD_NAME + "暫時不接受數據漫遊或新玩家注冊。\n"
                      "請訪問遊戲論壇：http://www.mudbuilder.com 獲得詳細的訊息，或重新嘗試連接。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif

#ifdef REFUSE_NEW_PLAYER
        write("對不起，目前" + MUD_NAME + "暫時不接受新玩家注冊。\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif

        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if( usr[i] != ob && query("id", usr[i]) == arg )
                        break;
        if( i >= 0 ) {
                write("有其他玩家正在使用這個 ID，請重新輸入。\n");
                write("您的英文名字：\n");
                input_to("get_id", ob);
                return;
        }

        if( query_temp("tomud", ob) )
                write(ALERT(NO_FEE_WARNING)+"使用"+query("id", ob)+
                        " 這個名字將會創造一個新的人物，您確定嗎(y/n)？");
        else
                write("使用"HIW+query("id", ob)+NOR"這個名字將會創造一個新的人物，您確定嗎("HIR"y"NOR"/"HIY"n"NOR")？");

        input_to("confirm_id", ob);
}

protected void get_wizpwd(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass=query("wizpwd", ob);

        if( crypt(pass, old_pass) == old_pass ) {
                write(HIG "身份確認完成，巫師專用密碼驗証通過！\n" NOR);
                write("請輸入密碼：\n");
                input_to("get_passwd", 1, ob);
                return;
        } else {
                write("密碼錯誤！\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
}

protected void confirm_cruiseid(string yn, object ob)
{
        int t;

        write("\n");
        if( upper_case(yn) == "Y" ) {
                if( cruise_lock ) {
                        write("對不起，目前該站已被天神臨時設置為禁止漫遊，如想要漫遊，請和天神聯系。\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write("請輸入該 ID 管理密碼：\n");
                input_to("get_cruisepwd", 1, ob);
                return;
        }
        write("你選擇重新注冊或登陸 ID，請重新輸入。\n");
        write("您的英文名字：\n");
        input_to("get_id", ob);
        return;
}

protected void get_cruisepwd(string pass, object ob)
{
        string sites;
        string passwd;
        write("\n");

#ifdef DB_SAVE
        passwd = DATABASE_D->db_query_user(query("id", ob), "ad_password");

        if( !stringp(passwd) || crypt(pass, passwd)[0..15] != passwd ) {
                write("密碼錯誤！\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        write("人物身份確認完成，開始連接站點服務器獲取人物的數據信息。\n");
        sites = DATABASE_D->db_query_user(query("id", ob), "last_station");
        CRUISE_D->authenticate_user(ob, sites);

        call_out("destruct_ob", 0, ob);
        return;
#else
        write("密碼錯誤！\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif
}

protected void get_passwd(string pass, object ob)
{
        string ad_pass;
        string my_pass;

        my_pass=query("password", ob);
        ad_pass=query("ad_password", ob);
        if( !stringp(my_pass) || crypt(pass, my_pass) != my_pass ) {
                if( !stringp(ad_pass) || crypt(pass, ad_pass) != ad_pass ) {
                        write("密碼錯誤！\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write(HIR "\n你採用了管理密碼進入遊戲，"
                      "因此請你先修改你的普通密碼。\n" NOR);

                // 做標記：表示目前流程是修改密碼分支。
                set_temp("reset_password", 1, ob);
                write("\n請重新設定您的普通密碼：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( !stringp(ad_pass) ) {
                write(HIC "\n請注意：你的ID目前還沒有管理密碼，請設置你的管理密碼。\n\n" NOR);
                write(HIW "在你普通密碼丟失的情況下，你可以輸入管理密碼進入，並修改普通\n"
                      "密碼，所以請你設置一個可靠的並且與普通密碼不同的管理密碼，用\n"
                      "來保護你的ID。平時請使用普通密碼登陸，避免過于頻繁的使用管理\n"
                      "密碼以導致潛在的泄漏風險。\n\n" NOR);
                write("請輸入你的管理密碼：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        check_ok(ob);
}

protected void reset_ad_password(string pass, object ob)
{
        string my_pass;
        write("\n");

        if( strlen(pass) < 5 ) {
                write("管理密碼的長度至少要五個字元，請重設您的管理密碼：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        my_pass=query("password", ob);
        if( stringp(my_pass) && crypt(pass, my_pass) == my_pass ) {
                write(HIR "為了安全起見，系統要求管理密碼的密碼和普通密碼不能相同。\n\n" NOR);
                write("請重新輸入你的管理密碼：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set_temp("ad_password", crypt(pass,0), ob);
        write("請再輸入一次您的管理密碼，以確認您沒記錯：\n");
        input_to("confirm_reset_ad_password", 1, ob);
}

protected void confirm_reset_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您兩次輸入的管理密碼並不一樣，請重新設定一次管理密碼：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);
        check_ok(ob);
}

protected void check_ok(object ob)
{
        object user;
        string *res;
        string str, str1, str2;
        int    on, fee, i, rec = 0;

        /*
        if( !BAN_D->vaild_allow_address(ob) ) {
                call_out("destruct_ob", 0, ob);
                return;
        }
        */
        // Check if we are already playing.
        user = find_body(query("id", ob));
        if( !objectp(user) )
                user = make_body(ob);
        else
                rec = 1;

        if( !objectp(user)) {
                write(HIR "無法創建該玩家，你可以嘗試重新登錄或是和巫師聯系。\n" NOR);
                return ;
        }

        if( rec != 1 && !user->restore()) { // 必須要判斷rec的值，否則會把玩家數據返回到前一次存儲的數據
                write(HIR "無法讀取該玩家數據，你可以嘗試重新登錄或是和巫師聯系。\n" + rec + NOR);
                return ;
        }

#ifdef NO_FEE
        if( query_temp("tomud", ob) )
                write(ALERT("文字MUD遊戲『王者之戰』將永久免費開放！請新老玩家相互轉告！\n"));
#else
        /*
        if( query("monfee", user)<time() && arrayp(res=query_temp("res", ob))){
                str1 = res[1] + "0";
                str2 = res[2] + "0";
                if( sscanf(str1, "%d", on) == 1 && sscanf(str2, "%d", fee) == 1 ) {
                        on /= 10;
                        fee /= 10;
                        i = onl / 3600;
                        str = "你總共購買遊戲時間： " + fee + " 個小時$$" +
                              "你已經在遊戲中進行了：" + i + "小時" + ((on % 3600) / 60) + "分鐘$$";
                        if( i >= fee )
                                str += "你購買的遊戲時間已經使用完了，請聯系『王者□□』小組繼續購買遊戲時間！$$遊戲主頁： http://www.mudzone.org $$";
                        else if( (fee - i) < 18 )
                                str+="你購買的遊戲時間已經只有 " + (fee - i - 1) + " 小時多一點了$$請趕快去 http://www.mudzone.org 給你的帳號續費吧$$";
                        else if( fee == i )
                                str += "你購買的時間已經不到一個小時了，請盡快去 http://www.mudzone.org 給你的帳號續費$$";
                        if( fee == 18 )
                                str += NO_FEE_WARNING;
                        write(ALERT(str) + ((fee > 18) ? TMI("regur good") : "") + TMI("dlurl 123.12586.com/images/face32/"));
                        if( i >= fee ) {
                                call_out("destruct_ob", 0, ob);
                                call_out("destruct_ob", 0, user);
                                return;
                        }
                        // write(ALERT("a"));
                }
                // else
                //         write(ALERT("b"));
        }
        // else
        //write(ALERT("c")+"FLAG:"+query("monfee", user)+""+time()+""+arrayp(res=query_temp("res", ob)));

        // Check if we are already playing.
        // user = find_body(query("id", ob));
        // if( user ) {
        */
#endif

        if( rec ) {
                if( user->is_net_dead() ) {
                        reconnect(ob, user);
                        return;
                }
                write("您要將另一個連線中的相同人物趕出去，取而代之嗎？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        } else {
                mixed err;
                string msg;

                log_file("usage", sprintf("%s(%s) loggined from %s (%s)\n",
                        query("name", user),query("id", user),
                        query_ip_number(ob), ctime(time()) ) );

                if( query("last_on", ob)<time() &&
                    query("last_on", ob)>time()-30 &&
                    !wiz_level(user) ) {
                        write("你距上一次退出時間只有"+chinese_number(time()-query("last_on", ob))+
                              "秒鐘，請稍候再登錄。\n");
                        call_out("destruct_ob", 0, user);
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                set_temp("logon_time", time(), user);
                set("last_save", time(), user);
                if( err = catch(waiting_enter_world(ob, user)) ) {
                        set_temp("debug_msg", err, user);
                        msg = HIR "\n你無法進入這個世界，可能你的檔案出了一些問題，需要和巫師聯系。\n\n" NOR;
                        if( mapp(err) )
                                msg += MASTER_OB->standard_trace(err, 1);
                        set_temp("error", msg, user);
                        write(msg);
                }
                return;
        }
}

protected void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( !yn || yn=="" ) {
                write("您要將另一個連線中的相同人物趕出去，取而代之嗎？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，歡迎下次再來。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( user ) {
                tell_object(user, "有人從別處( " + query_ip_number(ob)
                                + " )連線取代你所控制的人物。\n");
                log_file("usage", sprintf("%s(%s) replaced by %s (%s)\n",
                         query("name", user),query("id", user),
                         query_ip_number(ob), ctime(time())));

                // Kick out tho old player.
                old_link=query_temp("link_ob", user);
                if( old_link ) {
                        exec(old_link, user);
                        call_out("destruct_ob", 0, old_link);
                }
        } else {
                write("在線玩家斷開了連接，你需要重新登陸。\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("使用這個名字將會創造一個新的人物，請問您確定嗎("HIR"y"NOR"/"HIY"n"NOR")？");
                input_to("confirm_id", ob);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，那麼請重新輸入您的英文名字：");
                input_to("get_id", ob);
                return;
        }
        write(CLR);
        write("\n\n");
        write(HIW @TEXT

請輸入您的高姓大名，由于這個名字代表你的人物，而且以後不能更
改，務必慎重擇名（不雅觀的姓名將被刪除）。另：請不要選擇金庸
小說中已有人物姓名。

首先輸入的是你的姓，比如你想扮演角色叫張三，先輸入“張”，然
後電腦會詢問你的名字，那時你再輸入“三”。如果你想扮演的角色
的名字比較怪，比如叫“老虎”，可以不輸入姓，直接敲回車略過。
但是建議你還是輸入一個比較像樣子的姓名，而這些比較怪的稱號可
以用暱稱代替，否則某些地方的稱呼可能會比較怪。如果你要加入世
家，那麼你就不必輸入姓了，因為一旦加入世家將自動選擇家傳祖姓，
不是你自己決定的。

TEXT NOR
        );
        write("您的中文" HIG "姓氏" NOR "(不要超過兩個漢字)：\n");
        input_to("get_surname", ob);
}

protected void get_surname(string arg, object ob)
{
        if( arg && strlen(arg) > 0 ) {
#if 0
                if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                        // arg = B2G(arg);
                        arg = LANGUAGE_D->toGB(arg);
#else
                        arg = LANGUAGE_D->toGB(arg);
#endif
#endif
                if( !check_legal_name(arg, 4) ) {
                        write("您的中文" HIG "姓氏" NOR "(不要超過兩個漢字)：\n");
                        input_to("get_surname", ob);
                        return;
                }
                set("surname", arg, ob);
        } else {
                write("您的中文" HIG "姓氏" NOR "(不可以沒有姓氏)：\n");
                input_to("get_surname", ob);
                return;
        }
        write("您的中文" HIY "名字" NOR "(不要超過兩個漢字)：\n");
        input_to("get_name", ob);
}

protected void get_name(string arg, object ob)
{
        string fname;
        string result;

#if 0
        if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                // arg = B2G(arg);
                arg = LANGUAGE_D->toGB(arg);
#else
                arg = LANGUAGE_D->toGB(arg);
#endif
#endif
        if( !check_legal_name(arg, 4) ) {
                write("您的中文" HIY "名字" NOR "(不要超過兩個漢字)：\n");
                input_to("get_name", ob);
                return;
        }
        set("purename", arg, ob);

        fname=query("surname", ob);
        if( !stringp(fname) ) fname = "";
        fname += arg;

        if( strlen(fname) < 4 ) {
                write("對不起，你的中文名字（姓和名的組合）至少要有兩個漢字。\n");
                write("\n請重新輸入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }

        if( stringp(result = NAME_D->invalid_new_name(fname))
        ||  stringp(result = NAME_D->invalid_new_name(arg)) ) {
                write("對不起，" + result + "\n");
                write("\n請重新輸入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }

#ifdef DB_SAVE
        if( DATABASE_D->db_find_user("name", fname) ||
            DATABASE_D->db_find_user("name", arg) ) {
                write("對不起，你的姓名和其他站玩家的姓名重復或類似！\n");
                write("\n請重新輸入您中文" HIG "姓氏" NOR "：\n");
                input_to("get_surname", ob);
                return;
        }
#endif

        if( arg == query("surname", ob)){
                write(HIW "\n系統發現你輸入的姓和名字相同，這樣你的名字將是：“"
                      HIY + arg + arg + HIW "”。\n"
                      "你是否是因為不了解本系統而且沒有仔細閱讀前面的幫助而錯誤的輸入\n"
                      "了你的姓名，如果是，請你重新連接並輸入你的名字，否則請你輸入一\n"
                      "遍你的全名，表明你的確想使用這個名字。\n\n" NOR);
                write("請輸入您的全名(即姓和名字的組合)：\n");
                input_to("input_full_name", ob, arg + arg);
                return;
        }

        write(HIW "\n為了保証你的人物的安全，遊戲要求你設置兩個密碼。一個是管理密\n"
              "碼，這個密碼可以在你遺失了普通密碼時登錄遊戲，並用來修改普通\n"
              "密碼。平時請使用普通密碼登陸，避免過于頻繁的使用管理密碼以導\n"
              "致潛在的泄漏風險。\n\n" NOR);
        write("請設定您的管理密碼：\n");
        input_to("new_ad_password", 1, ob);
}

protected void input_full_name(string arg, object ob, string fname)
{
        if( arg != fname ) {
                write(WHT "\n你輸入的全名並不是你姓和名字的的組合，系統認為你開始沒有理解輸\n"
                      "入名字的要求，" HIR "請你仔細閱讀所有提示的條款，不要自作聰明"
                      NOR WHT "。包括在\n"
                      "今後的遊戲過程中請仔細閱讀各種幫助和公告，避免因為自以為是而導\n"
                      "致浪費時間或是遭受不必要的損失。\n" NOR);
                confirm_id("Yes", ob);
                return;
        }
        write("\n請設定您的管理密碼：\n");
        input_to("new_ad_password", 1, ob);
}

protected void new_ad_password(string pass, object ob)
{
        write("\n");
        if( strlen(pass) < 5 ) {
                write("管理密碼的長度至少要五個字元，請重設您的管理密碼：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("ad_password", crypt(pass,0), ob);
#endif

        write("請再輸入一次您的管理密碼，以確認您沒記錯：\n");
        input_to("confirm_ad_password", 1, ob);
}

protected void confirm_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您兩次輸入的管理密碼並不一樣，請重新設定一次管理密碼：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);

        write(HIW "普通密碼是你平時登錄遊戲時使用的，遊戲中可以通過 PASSWD 命令\n"
              "來修改這個密碼。\n\n" NOR);
        write("請輸入你的普通密碼：\n");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        string ad_pass;

        write("\n");
        if( strlen(pass) < 3 ) {
                write("密碼的長度至少要三個字元，請重設您的密碼：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( stringp(ad_pass=query("ad_password", ob)) &&
            crypt(pass, ad_pass) == ad_pass ) {
                write(HIR "請注意，為了安全起見，系統要求你的管理密碼和普通密碼不能相同。\n\n" NOR);
                write("請重新設置您的普通密碼：\n");
                input_to("new_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("password", crypt(pass,0), ob);
#endif

        write("請再輸入一次您的密碼，以確認您沒記錯：\n");
        input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("您兩次輸入的密碼並不一樣，請重新設定一次密碼：\n");
                input_to("new_password", 1, ob);
                return;
        }

        set("password", old_pass, ob);
        if( query_temp("reset_password", ob)){
                // 這是用戶修改自己的密碼分支流程，不是創建
                // 用戶分支，因此轉移到 check_ok 函數繼續執
                // 行。
                ob->save();
                check_ok(ob);
                return;
        }

        write("您要扮演男性(m)的角色或女性(f)的角色？\n");
        input_to("get_gender", ob);
}

protected void get_gender(string gender, object ob)
{
        object user;
        int id_tmp;
        string id_num;

        write("\n");
        if( gender == "" ) {
                write("您要扮演男性("HIG"m"NOR")的角色或女性("HIM"f"NOR")的角色？");
                input_to("get_gender", ob);
                return;
        }

        if( gender[0] == 'm' || gender[0] == 'M' )
                set_temp("gender", "男性", ob);
        else if( gender[0] == 'f' || gender[0] == 'F' )
                set_temp("gender", "女性", ob);
        else {
                write("對不起，您只能選擇男性("HIG"m"NOR")或女性("HIM"f"NOR")的角色：");
                input_to("get_gender", ob);
                return;
        }
        if( find_body(query("id", ob)) ) {
                write(HIR "這個玩家現在已經登錄到這個世界上了，請"
                      "退出重新連接。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() )
                DATABASE_D->connect_to_database();

        if( DATABASE_D->db_find_user("id",query("id", ob))){
                write(HIR "\n這個玩家現在已經在其他站注冊了，請退出重新連接。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif
        set("body", USER_OB, ob);
        if( !objectp(user = make_body(ob)) ) {
                write(HIR "\n你無法登錄這個新的人物，請重新選擇。\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
        set("str", 14, user);
        set("dex", 14, user);
        set("con", 14, user);
        set("int", 14, user);
        set("per", 20, user);
        set("kar", 20, user);
        set("gender",query_temp("gender",  ob), user);

        set("registered", 0, ob);
        set("registered", 0, user);
        log_file("usage", sprintf("%s(%s) was created from %s (%s)\n",
                          query("name", user),query("id", user),
                          query_ip_number(ob), ctime(time())));

        init_new_player(user);
        set_temp("newplayer", 1, user);
        waiting_enter_world(ob, user);
        write("\n");

        id_tmp = to_int(read_file(CONFIG_DIR + "reg_players", 1)) + 1;
        id_num = sprintf("%d", id_tmp);
        write_file(CONFIG_DIR + "reg_players", id_num, 1);
}

object make_body(object ob)
{
        string err;
        object user;

        if( !is_root(previous_object()) ){
                log_file("static/security",
                         sprintf("%s try to create player(%s) on %s.\n",
                                 (string)geteuid(previous_object()),
                                 query("id", ob),
                                 ctime(time())));
                write("你沒有權限創建玩家。\n");
                return 0;
        }

        seteuid(getuid());
        user = new(USER_OB);
        if( !user ) {
                write("現在可能有人正在修改使用者物件的程式，無法進行復制。\n");
                write(err+"\n");
                return 0;
        }
        seteuid(query("id", ob));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        set("id",query("id",  ob), user);
        set("surname",query("surname",  ob), user);
        set("purename",query("purename",  ob), user);
        user->set_name(0, ({ query("id", ob) }));
        return user;
}

private void init_new_player(object user)
{
        set("title", "普通百姓", user);
        set("birthday", time(), user);
        set("potential", 100, user);
        set("food", (query("str", user) + 10) * 10, user);
        set("water", (query("str", user) + 10) * 10, user);
        //set("channels", ({"chat","rumor","new","stock","info","sos","bill","family"}), user);
        set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
        CHANNEL_D->register_channel(user, query("channels")); 
        set("chann", (["sos":1,"tch":1,"auc":1]), user);//默認顯示在主窗口的頻道

        // 記錄名字
        NAME_D->map_name(query("name", user), query("id", user));

        set("monfee", time()+8640000, user);
        //set("env/prompt", "time", user);
        set("env/wimpy", 60, user);
        // 標準暫存訊息
	set("msg/chat", 1, user);
	set("msg/rumor", 1, user);
	set("msg/tell", 1, user);
	set("msg/say", 1, user);
	set("msg/emotion", 1, user);
        set("msg/size", 100, user);
        set("level", 1, user);
}

void waiting_enter_world(object ob, object user)
{
        string msg;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        set_temp("waiting_enter", 1, ob);//防止被銷毀

        if( file_size(NOTICE) > 0 ) {
                msg  = BLINK "□  " NOR + WHT + CHINESE_MUD_NAME + NOR +
                       HIK "公怖欄                          " NOR +
                       HIK + TIME_D->replace_ctime(stat(NOTICE)[1]) + "\n" NOR;
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
                msg += read_file(NOTICE);
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
        } else {
                msg = terminal_colour(color_filter(read_file(NOTICE_MOTD)), ([
                        "MUD_NAME"      : CHINESE_MUD_NAME,
                        "ENGLISH_NAME"  : INTERMUD_MUD_NAME,
                        "MUDLIB_VERSION": MUDLIB_VERSION_NUMBER,
                        "MUDOS_VERSION" : __VERSION__ ,
                        "ARCH"          : __ARCH__,
                        "UPDATE"        : TIME_D->replace_ctime(stat(NOTICE_MOTD)[1]),
                ]));
        }

        write(msg);

        write(WHT "請輸入任意鍵繼續或 " HIR + WAITING_ENTER_TIME + NOR + WHT " 秒後自動進入遊戲\n" NOR);
        set_temp("call_out_handle", call_out((:enter_world,ob,user,0,WAITING_ENTER_TIME:),1), ob);

        input_to( (: enter_world, ob, user, 0, 1 :) );
}

varargs void enter_world(object ob, object user, int silent, int timer, string arg)
{
        object cloth, shoe;
        string startroom;
        string place, address;
        string sql, ip_number;
        string msg;
        string *ret;
        object login_ob, *users;
        mapping marry;
        mixed err;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( !ob || !user ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( timer && --timer ) {
#ifdef LONELY_IMPROVED
                remove_input_to(ob);
#endif
                write(TOTOP(1) + WHT "請輸入任意鍵繼續或 " HIR + timer + NOR + WHT " 秒後自動進入遊戲\n" NOR);
                set_temp("call_out_handle", call_out((:enter_world,ob,user,silent,timer:),1), ob);
                input_to( (: enter_world, ob, user, silent, 1 :) );
                return;
        }

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
        set("registered",query("registered",  user), ob);
        delete_temp("waiting_enter", ob);

        if( intp(query_temp("call_out_handle", ob)) )
                remove_call_out(copy(query_temp("call_out_handle", ob)));

        delete_temp("call_out_handle", ob);
#ifdef LONELY_IMPROVED
        remove_input_to(ob);
#endif
        ob->clear_msg_buffer();

        //user->set_encoding(ob->query_encoding());
#if 0
        if( query_temp("big5", ob) ) set_temp("big5", 1, user);
#endif
        if( query_temp("tomud", ob) ) set_temp("tomud", 1, user);

        if( interactive(ob) ) exec(user, ob);
        user->setup();

        if( query("age", ob) == 14){
                set("food", user->max_food_capacity(), user);
                set("water", user->max_water_capacity(), user);
        }

#ifdef DB_SAVE
        if( query_temp("newplayer", user) && query("id", user) != "guest"){
                if( !DATABASE_D->query_db_status() )
                        DATABASE_D->connect_to_database();
                DATABASE_D->db_new_player(ob, user);
        }
#endif

#ifdef QUIT_SAVE_ALL
        if( query_temp("newplayer", user)){
                if( query("gender", user) == "女性"){
                        shoe = new("/clone/cloth/female-shoe.c");
                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                } else {
                        shoe = new("/clone/cloth/male-shoe.c");
                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                }
                cloth->move(user);
                //catch(cloth->wear());
                cloth->wear();
                shoe->move(user);
                //catch(shoe->wear());
                shoe->wear();
        } else {
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n你的身上物品檔案出了一些問題，需要和巫師聯系。\n\n" NOR);
                }
        }
#else
        if( !query_temp("newplayer", user)){
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n你的身上物品檔案出了一些問題，需要和巫師聯系。\n\n" NOR);
                }
        }
        if( wizhood(user) == "(player)" ) {
                if( query("class", user) == "bonze"){
                        if( query("gender", user) == "女性"){
                                cloth = new("/clone/cloth/ni-cloth.c");
                                shoe = new("/clone/cloth/ni-xie.c");
                        } else {
                                cloth = new("/clone/cloth/seng-cloth.c");
                                shoe = new("/clone/cloth/seng-xie.c");
                        }
                } else {
                        if( query("class", user) == "taoist"){
                                if( query("gender", user) == "女性"){
                                        cloth = new("/clone/cloth/daogu-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                } else {
                                        cloth = new("/clone/cloth/dao-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                }
                        } else {
                                if( query("gender", user) == "女性"){
                                        shoe = new("/clone/cloth/female-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                                } else {
                                        shoe = new("/clone/cloth/male-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                                }
                        }
                }
        } else {
                if( query("gender", user) == "女性"){
                        cloth = new("/clone/cloth/yunshang");
                } else {
                        cloth = new("/clone/cloth/jinduan");
                }
                shoe  = new("/clone/cloth/xianlv");
        }
        user->force_me("wear all"); // 其他下線不丟的防具先傳上
        cloth->move(user);
        //catch(cloth->wear());
        cloth->wear();
        shoe->move(user);
        //catch(shoe->wear());
        shoe->wear();
        if( cloth && (!environment(cloth) || !query("equipped", cloth)) )
                destruct(cloth);
        if( shoe && (!environment(shoe) || !query("equipped", shoe)) )
                destruct(shoe);
#endif
        if( user->over_encumbranced() )
                write(HIY ">>>>>>>> 你已超重. <<<<<<<<\n" NOR );

        user->save();
        ob->save();

        UPDATE_D->check_user(user);

        if( !silent ) {
                write("\n\n");

                if( !query("registered", user)){
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", REGISTER_ROOM, user);
                } else
                if( !stringp(query("born", user)) ) {
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", BORN_ROOM, user);
                } else
                if( query("reborn_lunhui", user) || query("hell_quest", user) || query("over_quest/hell_quest", user) ) {
                        set("startroom", "/d/death/youmingdian", user);
                }

                if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" )
                        startroom = WIZARD_ROOM;
                else if( user->is_in_prison() )
                        startroom = user->query_prison();
                else if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else {
                        startroom=query("startroom", user);
                        if( !stringp(startroom)
                        ||  file_size(startroom + ".c") < 0
                        ||  startroom == CHAT_ROOM
                        ||  startroom == DEATH_ROOM )
                                startroom = START_ROOM;
                }

                if( !catch(load_object(startroom)) )
                        user->move(startroom);
                else {
                        startroom = START_ROOM;
                        user->move(startroom);
                        set("startroom", startroom, user);
                }

                if( !query("registered", user) )
                        write(color_filter(read_file(UNREG_MOTD)));
                else
                        write(color_filter(read_file(MOTD)));

                write("你連線進入" + MUD_NAME + "。\n");
                tell_room(startroom,query("name", user)+
                          "連線進入這個世界。\n", ({ user }));

#ifdef MCCP_SUPPORT
                if( !compressedp(user) )
                        write(YEL "你所使用的連線軟體未啟動網路傳輸壓縮("
                              HIY "MCCP" NOR YEL ")功能，建議您啟動該功能讓網路更加順暢。\n" NOR);
#endif
        }

        if( query("id", user) == "guest"){
                write(HIG "\n>>>>> 歡迎你來到這裡參觀。\n" NOR);
                user->guest_count();
        }

        login_ob = new(LOGIN_OB);
        set("id",query("id",  user), login_ob);
        login_ob->restore();
        if( !query("login_times", login_ob)){
                //write(NOR "你是第一次光臨" + MUD_NAME + "。\n");
                write(HIG "\n>>>>> 歡迎你第一次來到這個世界！:)\n" NOR);
                set("login_times", 1, ob);
        // show rules
        } else {
                addn("login_times", 1, ob);
                write("你上次光臨" + MUD_NAME + "是 " + HIG +
                        ctime(query("last_on", login_ob))+NOR+"從"+HIR+
                        query("last_from", login_ob)+NOR+"連接的。\n");
        }
        destruct(login_ob);

        /*
        if( query_temp("no_allow_ip", ob) )
                write(HIR "警告：你未設定自己的登錄地址范圍。請用" HIY " allowip " HIR "指令設置。\n" NOR);
        */
#ifdef DB_SAVE
        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)由%s(%s，%s)連線進入。", user->name(), query("id", user), query_ip_number(user), place, address);
        }
        else
#endif
                msg = sprintf("%s(%s)由%s連線進入。", user->name(), query("id", user), query_ip_number(user));

        if( !(wizardp(user) && query("env/no_loginmsg", user)) )
                CHANNEL_D->do_channel(this_object(), "sys", msg);

#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", user),"online",1);
        DATABASE_D->db_set_player(query("id", user),"last_station",LOCAL_STATION);
#endif

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(user);
#endif

       if( /*wizhood(user) != "(admin)" &&*/
           query("log_by/" + query("id", user), get_object(EXAMINE_D)) )
                user->start_log();

#ifdef DB_SAVE
        if( user->is_vip() && !BAN_D->is_netclub(query_ip_number(user)) )
#else
        if( BAN_D->is_welcome(query("id", user)) && !BAN_D->is_netclub(query_ip_number(user)) )
#endif
                BAN_D->open_club_line(user);    // 自動開放網吧限制

        // notice user the user of this mud
        NEWS_D->prompt_user(user);
        MSG_CMD->main(user, "system");
        ANALECTA_D->prompt_user(user);
        TOPTEN_D->topten_checkplayer(user);
        FESTIVAL_CMD->main(user);

        if( mapp(marry=query("couple", user)) && !undefinedp(marry["couple_id"])){
                string tmpstr, tmpstr1;
                object couple_ob = find_player(marry["couple_id"]);
                if( couple_ob ) {
                        if( query("gender", user) != "男性"){
                                tmpstr1 = "夫君";
                                tmpstr  = "愛妻";
                        } else {
                                tmpstr1 = "愛妻";
                                tmpstr  = "夫君";
                        }
                        write(sprintf(WHT HIM "\n你的%s%s已經在這等了你好久了，快去找%s吧。。。\n" NOR,
                                      tmpstr1, couple_ob->name(), gender_pronoun(query("gender", couple_ob))));
                        tell_object(couple_ob, sprintf(WHT HIM "\n你的%s%s抑制不住對你的思念跑來看你啦，快去和%s打個招呼吧。。。\n" NOR,
                                                       tmpstr,user->name(),gender_pronoun(query("gender", user))));
                }
        }

        if( (query("qi", user)<0 || query("jing", user)<0) && living(user) )
                user->unconcious();

        if( !wizardp(user) || !query("env/invisible", user)){
                users = filter_array(users(), (: query_temp("tomud", $1) :));
                message("system", ADD2(user), users);
        }
        if( query_temp("tomud", user)){
                foreach( object player in users() )
                        tell_object(user, ADD2(player));
                user->force_me("inventory");
                user->force_me("wear all");
                user->force_me("cmdbar");
        }
}

varargs void reconnect(object ob, object user, int silent)
{
        string sql, ip_number;
        string place, address;
        string msg;
        string *ret;

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
#if 0
        if( query_temp("big5", ob) )
                set_temp("big5", 1, user);
        else
                delete_temp("big5", user);
#endif

        if( query_temp("tomud", ob) )
                set_temp("tomud", 1, user);
        else
                delete_temp("tomud", user);

        exec(user, ob);
        user->reconnect();

        if( !silent && (!wizardp(user) || !query("env/invisible", user))){
                tell_room(environment(user),query("name", user)+YEL"重新連線回到這個世界。\n"NOR,
                ({user}));
        }

        if( query_temp("tomud", user)){
                user->force_me("look");
                user->force_me("inventory");
                user->force_me("cmdbar");
        }
#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", user), "online", 1);

        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)由%s(%s，%s)重新連線進入。",query("name", user),query("id", user),query_ip_number(user),place,address);
        }
        else
#endif
        msg = sprintf("%s(%s)由(%s)重新連線進入。",query("name", user),query("id", user),query_ip_number(user));
        CHANNEL_D->do_channel( this_object(), "sys", msg );

}

int check_legal_id(string id)
{
        int i;
        i = strlen(id);

        if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
                write("對不起，你的"+HIW"英文"NOR+"名字必須是 3 到 10 個英文字母。\n");
                return 0;
        }

        if( member_array(id, banned_id) != -1 ) {
                write("對不起，" HIC"“" + id + "”" NOR"這個詞有著特"
                      "殊的含意，不能用做英文名字。\n");
                return 0;
        }

        while(i--) {
                if( id[i]<'a' || id[i]>'z' ) {
                        write("對不起，你的"+HIW"英文"NOR+"名字只能用英文字母。\n");
                        return 0;
                }
        }
        return 1;
}

int check_legal_name(string name, int maxlen)
{
        int i;

        i = strlen(name);
//        if( (strlen(name) < 2) || (strlen(name) > maxlen) ) {
	maxlen *= 3;
        if( (strlen(name) < 3) || (strlen(name) > maxlen) ) {
                write("對不起，你的中文姓名不能太長或太短。\n");
                return 0;
        }

        if( !is_chinese(name) ) {
                write("對不起，請您用「中文」取名字。\n");
                return 0;
        }

        if( member_array(name, banned_name) != -1 ) {
                write("對不起，這種名字會造成其他人的困擾。\n");
                return 0;
        }

        //if( member_array(name, banned_name) % 2 == 0 )
        for( i=0; i<sizeof(banned_name); i++ ) {
                if( strsrch(name, banned_name[i]) != -1 ){
                        write("對不起，這種名字會造成其他人的困擾。\n");
                        return 0;
                }
        }
        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for( int i=0; i<sizeof(body); i++ ) {
                if( clonep(body[i]) &&
                    getuid(body[i]) == name ) {
                        if( !userp(body[i]) )
                                destruct(body[i]);
                        else    return body[i];
                }
        }
        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}

int set_cruiselock(int level)
{
        if( wiz_level(this_player(1)) <= 4 )
                return 0;

        cruise_lock = level;
        return 1;
}

int set_madlock(int setmark)
{
        if( wiz_level(this_player(1)) < wiz_level("(arch)") )
                return 0;
        if( setmark == 1 ) mad_lock = 1;
        else    mad_lock = 0;
        return 1;
}

int get_madlock()
{
        return mad_lock;
}

int can_login(int level)
{
        if( level < wiz_lock_level )
                return 0;

        return 1;
}

int block_ip(string ip, int time, string reason)
{
        mapping tmp_ban = ([]);

        tmp_ban["reason"] = reason;
        tmp_ban["time"] = time();
        tmp_ban["punish"] = time;
        map_delete(blocks, ip);
        blocks[ip] = tmp_ban;

        return 1;
}

int unblock_ip(string ip)
{
        if( ip == "all" )
                blocks = ([]);
        else
                map_delete(blocks, ip);

        return 1;
}

mapping query_block()
{
        return blocks;
}
