// skip.c

#include <command.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        mixed list;
        mixed info;
        string msg;

        list=query_temp("tell_list", me);
        if (arrayp(list) && sizeof(list) > 0)
        {
                if (arg == "all")
                {
                        // 顯示所有的歷史信息
                        msg = "以下是你收到的所有信息：\n";
                        foreach (info in list)
                        {
                                if (! arrayp(info) || sizeof(info) < 3 ||
                                    ! stringp(info[2]))
                                        // 這條歷史信息不合法
                                        continue;
                                msg += info[2];
                        }
                        if (strlen(msg) < 1024)
                                tell_object(me, msg);
                        else
                                // 消息太多
                                me->start_more(msg);

                        delete_temp("tell_list", me);
                        delete_temp("reply", me);
                        return 1;
                }

                // 去掉一條消息
                list = list[1..<1];

                // 整理一下，取出下一條歷史信息
                while (sizeof(list) > 0)
                {
                        info = list[0];
                        if (! arrayp(info) || sizeof(info) < 3 ||
                            ! stringp(info[0]) ||
                            ! stringp(info[1]) ||
                            ! stringp(info[2]))
                        {
                                // 這條歷史信息不合法
                                list = list[1..<1];
                                continue;
                        }

                        // 找到了合法的歷史信息
                        set_temp("reply", info[1], me);
                        if (strlen(info[2]) < 1024)
                                tell_object(me, info[2]);
                        else
                                // 歷史消息太長，需要用MORE方式顯示
                                me->start_more(info[2]);
                        break;
                }

                if (sizeof(list) < 1)
                {
                        // 已經沒有任何消息了
                        delete_temp("tell_list", me);
                        delete_temp("reply", me);
                        if (previous_object() != find_object(REPLY_CMD))
                                write("現在沒有任何歷史消息了。\n");
                        return 1;
                } else
                        set_temp("tell_list", list, me);
        } else
        {
                if (! undefinedp(list))
                        delete_temp("tell_list", me);

                if (previous_object() != find_object(REPLY_CMD))
                        write("你現在並收到沒有任何消息。\n");
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：skip [all]

如果你和別人交談的時候設置了阻塞方式的交談，那麼在你回答某人
信息之前系統不會將其他任何你的交談信息發送給你。如果你不需要
回答，直接想看下面的信息，就可以用 skip 命令略過。而skip all
則忽略所有信息。如果你設置的是半阻塞方式，那麼即使你回答某人
信息，系統也不會跳到下一條信息，必須手工輸入skip命令。在有信
息阻塞的時候，你的提示符 > 會變成綠色。

這條命令可以用 . 來代替。

see also : tell、reply
HELP );
        return 1;
}