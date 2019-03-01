// shutdown.c

#include <net/daemons.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *user, link_ob;
        int i;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        
        message_system("遊戲重新啟動，請稍候再登錄。");

        user = users();
        for (i = 0; i < sizeof(user); i++)
        {
                catch(user[i]->save());
                set_temp("block_msg/all", 1, user[i]);
                link_ob=query_temp("link_ob", user[i]);
                if (objectp(link_ob)) catch(link_ob->save());
        }

        if (find_object(INTERMUD2_D))
                catch(INTERMUD2_D->mud_shutdown());

        if (find_object(DBASE_D))
                catch(DBASE_D->mud_shutdown());

        shutdown(0);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: shutdown
 
強行重新起動遊戲，並且不保存任何運行中的數據。
 
HELP );
        return 1;
}
