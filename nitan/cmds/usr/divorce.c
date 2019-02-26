// divorce.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object witness;
        mapping couple;
        object  user;
        string  msg;

        seteuid(getuid());

        if( !mapp(couple=query("couple", me)) )
                return notify_fail("你現在好像是單身一人吧？\n");

        if (! arg)
                return notify_fail("你要和誰解除婚約？\n");

        if( arg == query("id", me) )
                return notify_fail("瘋了...你真的瘋了...\n");

        if( arg != query("couple/couple_id", me) )
                return notify_fail("這人和你現在並不是夫妻關係啊！\n");

        if (objectp(witness = present("marriage witness", environment(me))))
                return witness->do_divorce(me);

        if( !query_temp("pending/want_divorce", me) )
        {
                write("你身邊連個證婚的人都沒有，就像草草的離了"
                      "算了？要是這樣，你就在輸入一次這個指令表示決心。\n");
                set_temp("pending/want_divorce", 1, me);
                return 1;
        }

        write("你下定決心，一定要和"+query("couple/couple_name", me)+"徹底分手！\n");

        CHANNEL_D->do_channel(me, "chat",
                "我" + me->name(1) + "從今天起就和" + couple["couple_name"] +
                "(" + couple["couple_id"] + ")徹底斷絕關係！");

        user = find_player(couple["couple_id"]);
        if (user)
        {
                switch(query("character", user) )
                {
                case "光明磊落":
                        msg = "天哪！" + me->name(1) + "你這沒有良心的" +
                              RANK_D->query_rude(me) + "！";
                        break;

                case "狡黠多變":
                        msg = "哼..哼！嘿！走吧，走吧！";
                        break;

                case "心狠手辣":
                        msg = "好你個" + me->name(1) + "，咱們走着瞧！";
                        break;

                default:
                        msg = "很好，" + me->name(1) + "你等着吧！";
                        break;
                }

                CHANNEL_D->do_channel(user, "chat", msg);
        }

        UPDATE_D->clear_user_data(query("id", me),"couple");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : divorce
 
離婚。意思就是以後各走各的路。
 
see also : divorce
HELP );
    return 1;
}