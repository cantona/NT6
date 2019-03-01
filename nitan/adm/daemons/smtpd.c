/**************************
 *                        *
 * /adm/daemons/smtp_d.c  *
 *                        *
 * by Find@TX.            *
 *                        *
 **************************/

#include <net/socket.h>
#include <login.h>
#include <ansi.h>
#include <origin.h>
#include <mudlib.h>

#define PUBLIC_MUD_MAIL         "lonely-21@163.com"
#define RANDOM_PWD_LEN          8 /* 隨機密碼長度 */
#define REGFILE                 "/data/mail_reg.o"
#define REG_ROOM                "/d/register/regroom"
#define BASE64_D                "/adm/daemons/base64d"

inherit F_SAVE;

// class類型是C++新增的，想不到LPC也支持
class email
{
        string rcpt;    // 收件者地址
        string body;    // 內容
        int status;     // 狀態碼
        string id;      // 用戶 ID
        string passwd;  // 密碼
        object user;
        int normal;
}

protected void write_callback(int fd,string outgoing);
protected varargs void write_callback(int fd,string outgoing);
protected void close_callback(int fd);
protected int permit_reg_email(string mail);
protected int mail_have_reg(object user,string mail);
string    random_passwd(int len);
void      check_user(object user);

/*
 * 這裡是服務器你的登陸名和密碼。有一些服務器發信也是要進行
 * 身份認証的，現在不少提供商深受垃圾郵件毀壞名譽之苦，越來
 * 越多的採用發信身份認証，就像用 Outlook express 設置服務
 * 器必須選擇“我的服務器要求身份認証”。
 * 這個程序 SMTP 和 ESMTP 都可用，如果你的服務提供商不要求
 * 身份認証，你盡可以不理會這個設定。
 */
// ESMTP在新的FoxMail v3.11也支持。

string  *mail_reg; // 這裡保存已注冊的Email地址。
mapping user_unreg=([]); // 這裡保存郵件已發出但尚未確認的用戶的ID

protected string mailname = "lonely-21",mailpasswd = "921121";

protected mixed content = ([]);

/* 這裡設定你的 SMTP 服務器的域名和 IP 地址 */
protected string domain_name = "smtp.163.com", address = "123.125.50.135";

/*
 * 下面這部分是進行 SMTP 服務器 IP 地址的解析用的。
 * 一般 SMTP 服務器的域名是不會變的，但 IP 地址有可
 * 能變化。而且在遊戲運行中很少會注意這個。一旦出現
 * 變化是很麻煩的，263 有一次就改變了 IP 地址也沒有
 * 通知我們，我到三天以後才發現，搞的我很尷尬，因此
 * 加上了這個功能。
 */
protected void resolve_callback( string o_address, string resolved, int key )
{
        if( stringp(resolved) && (resolved != "") && (address != resolved) )
        {
                address = resolved;
                save();
                restore();
                log_file("smtp",sprintf("SMTP: 遠程 SMTP 郵件服務器IP地址被轉換為 %s\n",address));
        }
}

/* 這個函數我們是由 CRON_D 定時呼叫的，我們是1小時檢查一次。*/
void update_mail_server_ip()
{/*
        if(previous_object() && (geteuid(previous_object()) != ROOT_UID))
        return;*/
        resolve( domain_name, "resolve_callback" );
}

string query_save_file()
{
        return REGFILE;
}

protected void create()
{
        seteuid(getuid());
        if (file_size(REGFILE)<=0){
                mail_reg=({});
                user_unreg=([]);
                save();
        }
        restore();
        resolve( domain_name, "resolve_callback" );
}

/*
 * 這個函數是由玩家注冊用的那個房間裡的注冊命令
 * 呼叫的，user 是進行注冊的玩家物件，mail 是注
 * 冊的電子郵件地址。
 * 謹慎的人應當對呼叫此函數的物件進行一下檢查。
 */


void register_mail(object user,string mail)
{
        object link;
        string msg,passwd,server;
        int s,err;
        class email newmail;

        if(!user) return;
        if(!stringp(mail) || mail == "") return;

        mail = lower_case(mail);

        if( !objectp(link=query_temp("link_ob", user)) )
        {
                tell_object(user,"您的檔案不完全，無法進行注冊，請重新連線完成注冊.\n\n");
                destruct(user);
                return;
        }

        if(strsrch(mail,',') >= 0)
        {
        write(sprintf("你的電子郵件地址：%s 裡包含非法字符，\n請認真檢查後重新注冊。\n",mail));
        return;
        }

        if(mail_have_reg(user,mail)) return;

        passwd = random_passwd(RANDOM_PWD_LEN);
        server = sprintf("%s 25",address);

        /*
         * PUBLIC_MUD_MAIL 是在其它的地方定義的，就是遊戲
         * 對外交流的電子郵件地址。
         */
        msg = sprintf("From: \"%s\" <%s>\nTo: %s\nSubject: 您在%s的密碼\n\n",
        MUD_NAME,PUBLIC_MUD_MAIL,mail,CHINESE_MUD_NAME);
        msg+=sprintf(user->name()+"，你好，感謝您光臨"+MUD_NAME+"網絡遊戲。\n\n您的賬號：%s\n密碼：%s\n",query("id", user),passwd);
        msg += "\n注意：這個賬號目前為臨時賬號，請您于48小時之內登陸確認。\n";
        msg +=   "\t  過期未登陸將會被自動刪除。\n";
        msg +=   "\t  如有注冊登陸方面的問題可以與 "+ PUBLIC_MUD_MAIL+" 聯系。\n";
        msg += "\n\t  本遊戲的主頁在 "+MUD_WEB+"
          那裡有詳細的幫助和玩家寫的新手指南、經驗介紹，相信會\n\t  對你很有用處。

                 祝您在"+CHINESE_MUD_NAME+"玩的愉快！";

        newmail = new(class email);
        newmail->rcpt = mail;
        newmail->body = msg;
        newmail->id=query("id", user);
        newmail->passwd = passwd;
        newmail->user = user;
        user->start_busy(100);

        s = socket_create(STREAM,"read_callback", "close_callback");
        if(s<0)
        {
                log_file("socket","Socket create err: "+socket_error(s)+"\n");
                tell_object(user,"注冊過程中服務器發生錯誤，請再注冊一次。\n");
                return;
        }

        content += ([ s : newmail ]);

        err = socket_connect(s,server,"read_callback", "write_call_back");
        if(err < 0)
        {
                map_delete(content,s);
                log_file("socket","Socket connect err: "+socket_error(err)+"\n");
                tell_object(user,"注冊過程中服務器發生錯誤，請再注冊一次。\n");
                socket_close(s);
                return;
        }

        tell_object(user,"郵件發送中，請稍候1分半鐘．．．．．\n");
        call_out("time_out",90,s);
}

protected void time_out(int fd)
{
        class email mailmsg;

        if(undefinedp(content[fd]))
                return;

        mailmsg = content[fd];

        if(objectp(mailmsg->user))
        {
                tell_object(mailmsg->user,"\n發送過程超時，請重新再試一次。
                問題有可能是：SMTP郵件服務器的IP地址已經更改。\n");
                (mailmsg->user)->stop_busy();
        }

        map_delete(content,fd);
        socket_close(fd);
}

void send_mail(object user, string mail_from, string mail_to, string topic, string data)
{
        string server;
        int s, err;
        class email newmail;

        if(strlen(data) > 65536)
        {
                write("你不能發送大于64K的郵件。\n");
                return;
        }

        log_file("mail", sprintf("%s %s try to send mail <%s> Size:%d\n",
                                 log_time(),(user?query("id", user):"SYSTEM"),
                                 topic, strlen(data)));

        if(!mail_from || sscanf(mail_from, "%*s@%*s") != 2)
                mail_from = "lonely-21@163.com";

        if(!mail_to || sscanf(mail_to, "%*s@%*s") != 2)
        {
                write("無法向這個地址發送郵件。\n");
                return;
        }

        mail_to = lower_case(mail_to);

        if(strsrch(mail_to, ',') >= 0)
        {
                write(sprintf("電子郵件地址：%s 裡包含非法字符，無法發送。\n", mail_to));
                return;
        }

        server = sprintf("%s 25",address);

        newmail = new(class email);
        newmail->rcpt = mail_to;
        newmail->body = data;
        newmail->id=(user?query("id", user):"SYSTEM");
        newmail->passwd = "abcdefg";
        newmail->user = 0;

        s = socket_create(STREAM,"read_callback", "close_callback");
        if(s<0)
        {
                log_file("socket","Socket create err: "+socket_error(s)+"\n");
                write("郵件發送過程中服務器發生錯誤，請重試一次。\n");
                return;
        }

        content += ([ s : newmail ]);

        err = socket_connect(s,server,"read_callback", "write_call_back");
        if(err < 0)
        {
                map_delete(content,s);
                log_file("socket","Socket connect err: "+socket_error(err)+"\n");
                write("郵件發送過程中服務器發生錯誤，請重試一次。\n");
                socket_close(s);
                return;
        }

        tell_object(user,"郵件發送中，請稍候1分半鐘．．．．．\n");
        call_out("time_out",90,s);
}

protected void success_register(int fd)
{
        class email mailmsg;
        object usr,link;

        if(undefinedp(content[fd]))
                return;

        mailmsg = content[fd];
        if(!objectp(usr = mailmsg->user))
                return;
        if( !objectp(link=query_temp("link_ob", usr)) )
                return;

        (mailmsg->user)->stop_busy();
        map_delete(content,fd);
        tell_object(usr,sprintf("給您分配的隨機密碼已根據您登記的地址發往："HIW"%s"NOR"
請您"HIG"五分鐘"NOR"後檢查您的郵箱。如果您在"HIC"24"NOR"小時後還未能收到我們
給您發出的郵件，請您向 "HIY"%s"NOR" 發信說明詳細情況，
我們會盡快為您解決。不便之處請多諒解。
祝您在%s玩的愉快，再見！\n",mailmsg->rcpt,PUBLIC_MUD_MAIL,MUD_NAME));

        mail_reg=mail_reg+({mailmsg->rcpt});
        save();
        restore();

        set("last_on", time(), link);
        set("last_from", query_ip_name(usr), link);
        set("email", mailmsg->rcpt, link);
        set("oldpass",query("ad_password",  link), link);
        set("ad_password", crypt(mailmsg->passwd,0), link);
        set("email", mailmsg->rcpt, usr);
        set("have_reg", 1, usr);
        delete("new_begin", usr);
        link->save();
        usr->save();
        tell_room(environment(usr),"你只覺得眼前一花，"+query("name", usr)+"不見了。\n",({usr}));
        message("channel:sys",sprintf(HIR"【郵件注冊精靈】"HIW"%s(%s)郵件發出退出遊戲。\n"NOR,
                usr->name(),geteuid(usr)),filter_array(users(),(: wizardp($1) :)));
        user_unreg[mailmsg->id]=time(); // 添加這個用戶的ID到未確認名單中
        log_file("smtp",sprintf("%s(%s)的郵件已經發往 %s。\n",usr->name(),geteuid(usr),mailmsg->rcpt));
        save();
        restore();
        destruct(link);
        destruct(usr);
}

protected void close_callback(int fd)
{
        socket_close(fd);
}

/* 此函數處理發送過程中的致命錯誤 */
protected void mail_error(int fd,string message)
{
        class email mailmsg;

        mailmsg = content[fd];

        log_file("smtp_err",sprintf("ERROR:\n%s\nid: %s\nmail: %s\n\n",
                        message,mailmsg->id,mailmsg->rcpt));

        if(objectp(mailmsg->user))
        {
                tell_object(mailmsg->user,sprintf("\n發送過程中出現異常錯誤：\n%s\n請重試一次。\n\n",
                        message));
                (mailmsg->user)->stop_busy();
        }

        map_delete(content,fd);
        socket_close(fd);
}

protected void read_callback(int fd,string message)
{
        int rcode,err;
        string mechanism;
        class email mailmsg;

        if(undefinedp(content[fd]))
        {
                socket_close(fd);
                return;
        }

        mailmsg = content[fd];

        rcode = atoi(message[0..2]);

        if(!rcode || (rcode > 500))
        {
                mail_error(fd,message);
                return;
        }

        if(!mailmsg->status)  // 握手連通
        {
                socket_write(fd,sprintf("EHLO %s\r\n",query_host_name()));
                mailmsg->status++;
                return;
        }

        if(mailmsg->status == 1) // server ready
        {
                if((rcode == 500))      // command not recognized
                {
                        if(mailmsg->normal)
                        {
                                mail_error(fd,message);
                                return;
                        }

                        socket_write(fd,sprintf("HELO %s\r\n",query_host_name()));
                        mailmsg->normal = 1;
                        return;
                }

                if(mailmsg->normal)
                {
                        socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
                        mailmsg->status = 3;
                        return;
                }

                if(sscanf(message,"%*sAUTH=%s\n%*s",mechanism) == 3)
                {

                        socket_write(fd,sprintf("AUTH %s\r\n",mechanism));
                        mailmsg->status = 2;
                        return;
                }

                // ESMTP 協議不需要認証
                socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
                mailmsg->status = 3;
                return;
        }

        if(mailmsg->status == 2)        // Authentication
        {
                string quest;

                if(rcode == 334)        // 認証提問
                {
                        /*
                         * 這裡是 ESMTP 協議的認証部分，ESMTP 協議規定
                         * 認証信息使用 BASE64 編碼。
                         * 這裡的 base64_decode 和 base64_encode 函數
                         * 就是 base64_d 裡面的 decode 和 encode 函數，
                         * 我們是定義成了 simul_efun。
                         */
                        quest = message[4..];
                        quest = replace_string(quest,"\n","");
                        quest = replace_string(quest,"\r","");
                        quest = BASE64_D->decode(quest);
                        if(quest[0..3] == "User")
                        {
                                socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailname)));
                                return;
                        }
                        else if(quest[0..3] == "Pass")
                        {
                                socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailpasswd)));
                                return;
                        }
                }

                // 認証通過
                socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
                mailmsg->status = 3;
                return;
        }

        if(mailmsg->status == 3)
        {
                socket_write(fd,sprintf("RCPT TO: <%s>\r\n",mailmsg->rcpt));
                mailmsg->status = 4;
                return;
        }

        if(mailmsg->status == 4)
        {
                socket_write(fd,sprintf("DATA\r\n"));
                mailmsg->status = 5;
                return;
        }

        if(mailmsg->status == 5)
        {
                if(rcode == 354)        // ready receive data
                {
                        err = socket_write(fd,sprintf("%s\r\n.\r\n",mailmsg->body));
                        if( (err < 0) && (err != EEALREADY) )
                                call_out("write_callback",1,fd,sprintf("%s\r\n.\r\n",mailmsg->body));
                        mailmsg->status = 6;
                        return;
                }
                else
                {
                        mail_error(fd,message);
                        return;
                }
        }

        if(mailmsg->status == 6)
        {
                socket_write(fd,sprintf("QUIT\r\n"));
                mailmsg->status = 7;
                return;
        }

        if((mailmsg->status == 7) && (rcode == 221))
        {
                success_register(fd);
                return;
        }

        mail_error(fd,message);
}

protected varargs void write_callback(int fd,string outgoing)
{
        int err;

        if(stringp(outgoing) && (outgoing != ""))
        {
                err = socket_write(fd,outgoing);

                if( (err < 0) && (err != EEALREADY) )
                {
                        call_out("write_callback",1,fd,outgoing);
                        return;
                }
        }
}

/*
 * 對玩家注冊的電子郵件地址的各類檢查就在這裡實現，
 * 可以根據自己的需要增減代碼。
 * 要加入對某些 mail 地址的限制，也在這裡實現。
 */

protected int mail_have_reg(object user,string mail)
{
        object link;
        string id;

        if(!user) return 1;
        link=query_temp("link_ob", user);
        if(!link) return 1;
        if(!stringp(mail)) return 1;

        id=query("id", user);

        if(member_array(mail,mail_reg)!=-1)
        {
                tell_object(user,"這個郵件地址已經注冊過了，本遊戲不允許同一地址多重注冊。\n對不起！\n");
                message("channel:sys",sprintf(HIR"【郵件注冊精靈】：%s(%s)注冊請求被拒絕，退出遊戲。\n"NOR,
                user->name(),geteuid(user)),filter_array(users(),(: wizardp($1) :)));
                destruct(user);
                destruct(link);
                rm(DATA_DIR + "login/" + id[0..0] + "/" + id + ".o");
                rm(DATA_DIR + "user/"  + id[0..0] + "/" + id + ".o");
                return 1;
        }

        else
                return 0;
}

/*
 * 超過48小時未連線確認刪除檔案
 * 這個函數我們是由 CRON_D 定時呼叫的，
 * 一小時檢查一次。
 */
void user_no_login()
{
        string *player;
        string time;
        string *name;
        object user,link;
        int i;

// 這兩句是用來檢查權限的
        if(!previous_object()||(geteuid(previous_object()) != ROOT_UID)&&(geteuid(previous_object()) != "lonely"))
                return;

        name=keys(user_unreg); // 獲得所有郵件已發出等待確認的用戶array
        for(i=0; i<sizeof(name); i++){
                if ((time()-user_unreg[name[i]])>=172800){ // 假如這些id的注冊時間與現在時間相差2天=48小時=172800秒
                        if (!sizeof(player)) player=({name[i]});
                        else player+=({name[i]}); // 在player 這個array中加入這個玩家
                        map_delete(user_unreg,name[i]); // 在原先的mapping中刪除這個玩家
                        save();
                        restore();
                }
        }

// 下面就是對player這個array的處理了
        if(!player || !sizeof(player)){
                message("system",HIW"．．．無符合條件的玩家" NOR,users() );
                return;
        }

        time = ctime(time());

        foreach(string one in player)
        {
                string f;

                if(objectp(user = find_player(one)))
                {
                        if( objectp(link=query("link_ob", user)) )
                        destruct(link);
                        destruct(user);
                }

                if(file_size(f = sprintf(DATA_DIR+"login/%c/%s.o",one[0],one)) > 0)
                        rm(f);
                if(file_size(f = sprintf(DATA_DIR+"user/%c/%s.o",one[0],one)) > 0)
                        rm(f);
                log_file("smtp",sprintf("(%s)超過48小時未連線確認被刪除。%s\n",one,time));
        }
}

/* 這個函數產生一個長度為 len 的隨機密碼 */
string random_passwd(int len)
{
        int cap,low,num,n;
        string passwd;
        string Random_Passwd ="ABCDEFGHIJKL1234567890mnopqrstuvwxyzabcdefghi1jk9MNOPQRS4TUVW9XYZ";

        if(!intp(len))
                return "12345";

        if(len < 4 || len > 8)
                len = 8;

        do
        {
                cap=0; low=0; num=0; passwd = "";
                for(int i=0;i<len;i++)
                {
                        n = random(sizeof(Random_Passwd));
                        if( Random_Passwd[n] <='Z' && Random_Passwd[n] >='A' )
                                cap++;
                        else if( Random_Passwd[n] <='z' && Random_Passwd[n] >='a' )
                                low++;
                        else if( Random_Passwd[n] <='9' && Random_Passwd[n] >='0' )
                                num++;
                        passwd += Random_Passwd[n..n];
                }
        }
        while(!cap || !low || !num);

        return passwd;
}

// 下面的這個函數時我加上為了處理48小時內已經登陸的玩家，從未注冊用戶列表中刪除這些玩家。
void finish_reg(string id)
{
        int i;

        for (i=0;i<sizeof(user_unreg);i++)
        if (intp(user_unreg[id])&&user_unreg[id]!=0)
        {
                map_delete(user_unreg, id);
                save();
                restore();
                return;
        }
}

// 下面的是我用來調試的接口函數
mapping query_users()
{return user_unreg;}

string *query_mail_reg() { return mail_reg; }

string query_smtp_info()
{
        string msg;
        msg="\n服務器域名："+domain_name;
        msg+=("\n服務器IP地址："+address);
        msg+=("\n用戶名："+mailname);
        msg+=(" 用戶密碼：*****");
        msg+="\n";
        return msg;
}

void remove_mail(string mail)
{
        mail_reg -= ({ mail });
        save();
}

void stop_reg(object ob)
{
        delete("ad_password", ob);
        set("ad_password",query("oldpass",  ob), ob);

        delete("have_reg", ob);
        delete("oldpass", ob);

        remove_mail(query("email", ob));
        map_delete(user_unreg,query("id", ob));
}