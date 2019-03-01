// reply.c

#include <ansi.h>
#include <command.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string target, mud;
        object obj;
        string no_tell, can_tell;
        string reply_out;

        if (! arg || arg == "")
                return notify_fail("你要回答什麼？\n");

        if( !stringp(target=query_temp("reply", me)) )
                return notify_fail("剛才沒有人和你說過話。\n");

        if (sscanf(target, "%s@%s", target, mud) == 2)
        {
                GTELL->send_gtell(lower_case(mud), lower_case(target), me, arg);
                write("網路訊息已送出，可能要稍候才能得到回應。\n");
                return 1;
        }

        obj = find_player(target);
        if (! obj || ! me->visible(obj))
        {
                if (MESSAGE_D->send_msg_to(me, target, arg))
                        return 1;
                return notify_fail("剛才和你說話的人現在已經離開遊戲了。\n");
        }

        no_tell=query("env/no_tell", obj);
        if (! wizardp(me) && (no_tell == "all" || no_tell == "ALL" ||
            is_sub(query("id", me),no_tell)) )
        {
                can_tell=query("env/can_tell", obj);
                if( !is_sub(query("id", me),can_tell) )
                        return notify_fail("這個人不想聽你羅嗦啦。\n");
        }

        if (playerp(obj) && obj->is_net_dead())
                return notify_fail("這個人現在不在線上，聽不到你的話。\n");

        if (! living(obj))
                return notify_fail("這人現在恐怕聽不到你說的話了...\n");

        reply_out = sprintf(HIG "%s回答你：%s\n" NOR,
                            me->name(1)+HIG"("+query("id", me)+")",arg);
        if( !TELL_CMD->notice_user(me->name(1),query("id", me),obj,reply_out) )
                return 1;

        // 成功的回答了
        write(HIG"你回答"+obj->name(1)+HIG+"("+query("id", obj)+
              ")：" + arg + "\n" NOR);

        me->add_msg_log("reply", "你回答" + obj->query_idname()+"："HIG + arg + NOR"\n" NOR);
        obj->add_msg_log("reply", sprintf("%s回答你："HIG"%s"NOR"\n" NOR,me->query_idname(), arg));
        if (query_idle(obj) >= 120)
                write(YEL "可是" + obj->name(1) +
                      YEL "已經在豬圈中發呆有" + chinese_number(query_idle(obj) / 60) +
                      "分鐘了，恐怕沒法聽到你的話。\n");

        // 如果選擇的不是全阻塞(2)，則自動忽略這條信息，顯示
        // 下一條信息。
        if( query("env/jam_talk", me) != 2 )
                SKIP_CMD->main(me, "");

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：reply <訊息>

你可以用這個指令和剛才用 tell 和你說話的使用者說話。在多人和
你交談的時候，這個命令通常不會那麼好用，因為有可能在你 reply
的時候又有人向你發送信息而導致你應答錯誤，在這種情況下你可以
設置參數jam_talk，選擇阻塞式交談。當你的提示符 >  的顏色變成
綠色的時候，意味你現在正收到其他人發送給你的交談信息。

see also : tell、skip
HELP );
        return 1;
}