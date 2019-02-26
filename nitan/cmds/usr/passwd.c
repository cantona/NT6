// passwd.c

#include <getconfig.h>
#include <ansi.h>

inherit F_CLEAN_UP;


int main(object me, string arg)
{
        object ob;

        if (me != this_player(1)) return 0;

        if (arg == "?")
        {
                write("特殊功能：SHUTDOWN、ADMIN。\n");
                return 1;
        }

        if (stringp(arg))
        {
                if (! SECURITY_D->valid_grant(me, "(admin)"))
                {
                        write("你沒有權限修改別人的口令。\n");
                        return 1;
                }

                if (wiz_level(me) < wiz_level(arg))
                {
                        write("你沒有權限修改這個人的口令。\n");
                        return 1;
                }

                seteuid(getuid());
                ob = find_player(arg);
                if (! ob)
                {
                        ob = new(LOGIN_OB);
                        set("id", arg, ob);
                        if (! ob->restore())
                        {
                                destruct(ob);
                                return notify_fail("沒有這個玩家。\n");
                        }
                        set_temp("create_temp", 1, ob);
                } else
                {
                        ob=query_temp("link_ob", ob);
                        while (ob && ob->is_character())
                                ob=query_temp("link_ob", ob);
                        if (! ob)
                        {
                                ob = new(LOGIN_OB);
                                set("id", arg, ob);
                                if (! ob->restore())
                                {
                                        destruct(ob);
                                        return notify_fail("這個人物缺少連接信息，請重新LOGIN。\n");
                                }
                                set_temp("create_temp", 1, ob);
                        }
                }

                write("請輸入("+query("id", ob)+")的新管理密碼：");
                input_to("get_new_ad_pass", 1, ob);
                return 1;
        }

        ob=query_temp("link_ob", me);
        if (! ob)
                return notify_fail("你的人物缺少連接信息，請重新LOGIN。\n");

        while(ob && ob->is_character())ob=query_temp("link_ob", ob);

        write("為了安全起見，請先輸入您管理密碼：");
        input_to("get_old_pass", 1, ob);
        return 1;
}

protected void get_old_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        write("\n");
        old_pass=query("ad_password", ob);
        if (! stringp(old_pass) || crypt(pass, old_pass) != old_pass)
        {
                write(HIR "密碼錯誤！請注意：你需要輸入的是管理密碼。\n" NOR);
                return;
        }
        write("請選擇你下一步操作：\n"
              "1. 修改管理密碼\n"
              "2. 修改普通密碼\n"
              "3. 不修改。\n"
              "你選擇(如果你不方便輸入數字，可以輸入select1、select2)：");
        
        input_to("select_fun", ob);
}

protected void select_fun(string fun, object ob)
{
        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        switch (fun)
        {
        case "1":
        case "select1":
                write("請你輸入新的管理密碼：");
                input_to("get_new_ad_pass", 1, ob);
                return;

        case "2":
        case "select2":
                write("請你輸入新的普通密碼：");
                input_to("get_new_pass", 1, ob);
                return;

        case "":
        case "3":
                write("操作完畢。\n");
                return;

        default:
                write("沒有這項功能。\n");
                return;
        }
}


string trans_char(int c)
{
        return sprintf("%c ", c);
}

protected void get_new_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        if (pass == "")
        {
                write("操作取消了。\n");
                return;
        }

        if (strlen(pass) < 3)
        {
                write("對不起，你的普通密碼長度必須大於三位，請重新輸入：");
                input_to("get_new_pass", 1, ob);
                return;
        }

        old_pass=query("ad_password", ob);
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\n為了安全起見，普通密碼和管理密碼不能一樣。\n\n" NOR);
                write("請重新輸入你的普通密碼：");
                input_to("get_new_pass", 1, ob);
                return;
        }

        write("\n請再輸入一次新的普通密碼：");
        input_to("confirm_new_pass", 1, ob, crypt(pass, 0));
}

protected void confirm_new_pass(string pass, object ob, string new_pass)
{
        object me;
        object body;
        string email;
        string msg;

        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        write("\n");
        if (crypt(pass, new_pass) != new_pass)
        {
                write("對不起，您兩次輸入的並不相同，請重新輸入你的普通密碼：");
                input_to("get_new_pass", 1, ob);
                return;
        }

        seteuid(getuid());
        if( !set("password",new_pass,ob) )
        {
                write("普通密碼變更失敗！\n");
                return;
        }       
#ifdef DB_SAVE 
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();   

        DATABASE_D->db_set_player(query("id", ob),"password",pass);
#endif          
        ob->save();
        me = this_player();
        log_file("static/passwd", sprintf("%s %s's normal passwd changed by %s(%s)\n",
                                          log_time(),
                                          query("id", ob),
                                          geteuid(me),
                                          interactive(me) ? query_ip_name(me)
                                                          : 0,
                                          ctime(time())));

        write("普通密碼變更成功。\n");
}

protected void get_new_ad_pass(string pass, object ob)
{
        string old_pass;

        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        if (pass == "")
        {
                write("操作取消了。\n");
                return;
        }

        if (strlen(pass) < 5)
        {
                write(HIR "\n對不起，為了安全起見，你的普通密碼長度必須大於五位。\n\n" NOR);
                write("請重新輸入新的管理密碼：");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

        old_pass=query("password", ob);
        if (stringp(old_pass) && crypt(pass, old_pass) == old_pass)
        {
                write(HIR "\n為了安全起見，管理密碼和普通密碼不能一樣。\n\n" NOR);
                write("請重新輸入你的管理密碼：");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

        write("\n請再輸入一次新的管理密碼：");
        input_to("confirm_new_ad_pass", 1, ob, crypt(pass, 0));
}


protected void confirm_new_ad_pass(string pass, object ob, string new_pass)
{
        object me;
        object body;
        string email;
        string msg;
        string passwd;

        if (! objectp(ob))
        {
                write("無法找到連接對象，此次操作中止了。\n");
                return;
        }

        write("\n");
        if (crypt(pass, new_pass) != new_pass)
        {
                write("對不起，您兩次輸入的並不相同，請重新輸入你的管理密碼：");
                input_to("get_new_ad_pass", 1, ob);
                return;
        }

        seteuid(getuid());
        if( !set("ad_password",new_pass,ob) )
        {
                write("管理密碼變更失敗！\n");
                return;
        }
#ifdef DB_SAVE 
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();  
                
        DATABASE_D->db_set_player(query("id", ob),"ad_password",pass);
#endif        
        ob->save();
        me = this_player();
        log_file("static/passwd", sprintf("%s %s's super passwd changed by %s(%s)\n",
                                          log_time(),
                                          query("id", ob),
                                          geteuid(me),
                                          interactive(me) ? query_ip_name(me)
                                                          : 0,
                                          ctime(time())));

        // 查找併發送mail
        if( geteuid(me) == query("id", ob) )
        {
                // 是本人在修改
                write("管理密碼變更成功。\n");
                return;
        } else
        {
                // 是其他人修改
                set("password", "55AA", ob);
                write("清除用户原有的普通密碼。\n");
                ob->save();
        }

        body = LOGIN_D->make_body(ob);
        {
                // 發送mail
                body->restore();
                email=query("email", body);
                destruct(body);
                msg = @LONG
Hello, %id.

感謝您參與網絡遊戲%MUD_NAME，您所使用的賬號(%id)的管理密碼現
已經被%me修改成為%passwd，下次登錄的時候請您使用新的管理密碼
登錄，並重新設置登錄使用的普通密碼。對此造成的不便敬請原諒。

                             %data
LONG ;
                msg=replace_string(msg,"%id",query("id", ob));
                msg = replace_string(msg, "%MUD_NAME", LOCAL_MUD_NAME());
                msg = replace_string(msg, "%me", me->name(1) + "(" + geteuid(me) + ")");
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));
                //MAIL_D->queue_mail(me, 0, email, "Password chanaged", msg);
        }

        write("你成功的修改了用户("+query("id", ob)+")的管理密碼。\n");

        if( query_temp("create_temp", ob) )
                destruct(ob);
}

int help(object me)
{
        write(@HELP
指令格式 : passwd <玩家>
 
這個指令可以修改你的人物密碼。如果是巫師，可以使用這個命令來
修改他人的管理密碼，修改以後系統會自動發信到玩家所註冊信箱通
知新的管理密碼。

HELP );
        return 1;
}
