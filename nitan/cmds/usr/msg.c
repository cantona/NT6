// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <command.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *data;
        string type, id;
        object  target;
        int     i, t, total, size;

        seteuid(ROOT_UID);

        MYGIFT_D->check_mygift(me, "newbie_mygift/msg");   

        if( arg == "clear" ) {
                me->clear_msg_log();
                write("清除掉所有的訊息紀錄。\n");
                me->save();
                return 1;
        }

        if( arg == "system" ) {
                t=query("msg/time", me);
                if( !t ) {
                        tell_object(me, WHT "歡迎您進入" + LOCAL_MUD_NAME() +
                                        WHT "，今後請使用" HIY " msg " NOR WHT
                                        "命令查閱郵件信息。\n" NOR);
                        set("msg/time", time(), me);
                        return 1;
                }
                data = me->query_mail();
                if( !arrayp(data) || !sizeof(data) ) {
                        tell_object(me, HIY "您沒有收到新郵件。\n" NOR);
                        return 1;
                }

                size = sizeof(data);
                total = 0;
                for( i=size-1;i>=0;i-=3 ){
                        if( to_int(data[i-2]) > t )
                                total++;
                        else
                                break;
                }
                if( !total )
                        tell_object(me, HIY "你目前沒有未曾閱讀過的郵件。\n" NOR);
                else
                        tell_object(me, sprintf(WHT "你目前一共有 " HIY "%d" NOR
                                        WHT " 條郵件還沒有閱讀，請使用("
                                        HIY "msg" NOR WHT ")命令閱讀。\n" NOR, total));
                return 1;
        }
        if( arg == "info" ) {
                mapping setup=query("msg", me);

                if( !mapp(setup) || !sizeof(keys(setup)-({ "size" })) )
                        return notify_fail("沒有設定紀錄任何訊息。\n");

                map_delete(setup, "size");
                write("目前設定的訊息紀錄項目："+implode(keys(setup), ", ")+"\n");
                return 1;
        }

        if( arg && (size = to_int(arg)) ) {
                if( size < 10 || size > 1000 )
                        return notify_fail("訊息最少紀錄 10 筆，最多紀錄 1000 筆。\n");

                set("msg/size", size, me);
                write("設定訊息紀錄筆數為 "+size+" 筆。\n");
                me->save();
                return 1;
        }

        if( arg && sscanf(arg, "mail %s", id) == 1 ) {
                if( !wizardp(me) && time()-query_temp("last_mail_msg", me)<60 )
                        return notify_fail(HIC "你在一分鐘內只能發送一條短消息。\n" NOR);

                if( id == query("id", me) )
                        return notify_fail(HIC "你有沒有問題，自己給自己寫信息？！\n" NOR);

                target = UPDATE_D->global_find_player(id);

                if( !objectp(target) )
                        return notify_fail("沒有這個玩家。\n");

                UPDATE_D->global_destruct_player(target, 1);

                /*
                if( !wizardp(me)
                     && !MEMBER_D->is_valid_member(query("id", me) )
                    && id != "lonely" )
                          return notify_fail("只有會員才能發送短消息。\n");
                */

                set_temp("last_send_msg", time(), me);
                write(HIG "請輸入短消息內容（長度不超過500個漢字）。\n" NOR);

                me->edit(bind((: call_other, __FILE__, "done", me, id :), me));

                return 1;
        }
        else if( arg && sscanf(arg, "+%s", type) == 1 ) {
                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) ) {
                        set("msg/"+type, 1, me);
                        write("開始紀錄 "+type+" 的訊息。\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("無法設定 "+type+" 這種訊息。\n");
        }
        else if( arg && sscanf(arg, "-%s", type) == 1 ) {

                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) ) 
                {
                        delete("msg/"+type, me);
                        write("停止紀錄 "+type+" 的訊息。\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("無法設定 "+type+" 這種訊息。\n");
        }

        if( wizardp(me) && arg && objectp(target = find_player(arg)) && wiz_level(target) <= wiz_level(me) )
                data = target->query_msg_log();
        else
                data = me->query_msg_log();

        size = sizeof(data);

        if( size ) {
                string *str;

                str = ({ (target?target->query_idname():"")+"共有 "+(size/3)+" 筆舊訊息紀錄：\n─────────────────────────────────────\n" });

                if( arg && !target ) {
                        for(i=0;i<size;i+=3)
                                if( data[i+1] == arg )
                                        str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                        //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                }
                else {
                        for(i=0;i<size;i+=3)
                                   str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                }

                str += ({ "────────────────────────────目前時刻 "HIW+ctime(time())[11..15]+NOR"──\n" });
                me->start_more(implode(str, ""));
                set("msg/time", time(), me);
                me->save();
        }
        else
                write(target?target->query_idname():""+"目前沒有任何訊息紀錄。\n");

        return 1;
}

void done(object me, string id, string msg)
{
        object ob;
        string mail, *mail_log;

        if( !me || !msg || msg == "" )
                return;

        // 檢查長度
        if( sizeof(msg) > 1000 ) {
                write("短消息過長，最長不能大于1000個字節。\n");
                return;
        }

        msg = replace_string(msg, "\"", "");
        if( objectp(ob = find_player(id)) ) {
                if( !wizardp(me) && ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "的短消息已滿！\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "【郵件信息】來自" + me->query_idname() + HIR "的郵件內容如下\n"HIW+msg+NOR"\n");
                ob->save();
                tell_object(ob, HIR "【郵件信息】你新收到一封來自" + me->query_idname() + HIR "的郵件(msg mail)。\n" NOR);
        } else {
#ifdef DB_SAVE
                mail = DATABASE_D->db_query_player(id, "f_mail");
                mail_log = restore_variable(mail);
                if( !arrayp(mail_log) ) mail_log = ({});

                if( wiz_level(id) < 1 ) {
                        if( !wizardp(me) && sizeof(mail_log) >= 60 ) {
                                tell_object(me, "對方的短消息已滿！\n");
                                return;
                        }
                } else {
                        if( sizeof(mail_log) >= 300 ) {
                                tell_object(me, "對方的短消息已滿！\n");
                                return;
                        }
                }
                msg = HIR "【郵件信息】來自" + me->query_idname() + HIR "的郵件內容如下\n"HIW+msg+NOR"\n";
                mail_log += ({ time(), "mail", msg });

                mail = save_variable(mail_log);
                DATABASE_D->db_set_player(id, "f_mail", mail);
#else
                ob = UPDATE_D->global_find_player(id);
                if( ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "的短消息已滿！\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "【郵件信息】來自" + me->query_idname() + HIR "的郵件內容如下\n"HIW+msg+NOR"\n");
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1);
#endif
        }

        tell_object(me, HIY "【郵件信息】你的短消息已經成功發送！\n" NOR);
        return;
}

int help(object me)
{
        write(@HELP
顯示最近收到的 1000 個聊天/謠言頻道或是密語訊息。

msg                     查看所有訊息的紀錄
msg 種類                查看某類訊息的紀錄，例如 msg mail 則僅查看 mail 信息
msg +種類               增加某類訊息的紀錄
msg -種類               停止某類訊息的紀錄
msg 筆數                設定訊息紀錄筆數，最少紀錄 10 筆，最多紀錄 1000 筆
msg clear               刪除所有訊息
msg info                查詢目前的訊息紀錄項目
msg mail <某人>         給某人(不在線上)留言

訊息種類包括：公開頻道(chat, rumor, ...), say, tell, ...

HELP );
        return 1;
}
