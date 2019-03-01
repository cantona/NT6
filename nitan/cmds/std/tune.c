// tune.c

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

int main(object me, string arg)
{
        int my_channels = query("channels", me), flag;
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D));
        class channel_class ch;

        if( !arg )
        {
                tell(me, "你正在使用中的頻道有："+CHANNEL_D->query_using_channel(me)+"。\n");
                return 1;
        }
        
        if( wizardp(me) && sscanf(arg, "-l %s", arg) ) flag = 1;

        if( undefinedp(ch = channels[arg]) || !classp(ch) )
                return notify_fail("沒有這個頻道。\n");

        if( !(ch->number & my_channels) && (wiz_level(me->query_id(1)) < ch->level) )
                return notify_fail("沒有這個頻道。\n");

        if( flag )
        {
                string *names;
                names = CHANNEL_D->query_channel_users(arg)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "目前收聽 " + arg + " 頻道的共 " + sizeof(names) + " 人如下：\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");

                names = CHANNEL_D->query_channel_users(arg, 1)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "其余 " + sizeof(names) + " 人如下：\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");
                return 1;
        }

        if( ch->number & my_channels )
        {
                set("channels", my_channels ^ ch->number, me);
                CHANNEL_D->remove_register(me, ch->number);
                tell(me, "關閉 "+arg+" 頻道。\n");
        }
        else
        {
                set("channels", my_channels | ch->number, me);
                CHANNEL_D->register_channel(me, ch->number);
                tell(me, "開啟 "+arg+" 頻道。\n");
        }
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：tune [<頻道名稱>]

這個指令讓你選擇是否要收聽某一頻道的訊息，如果沒有指定頻道名稱，就會列出
你目前收聽中的頻道，如果指定了頻道，原來收聽中的就會關掉，反之打開。

如果你對一個沒有收聽中的頻道講話，會自動將它打開。
要對一個頻道講話，只要用：

<頻道名稱> <訊息> ....

例子：
  chat hello everyone!

你可以用 help channels 查詢目前有哪些頻道可以收聽。

see also : chat, rumor ...
HELP
        );
        return 1;
}
