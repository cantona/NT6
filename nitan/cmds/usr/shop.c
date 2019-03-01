// shop.c

inherit F_CLEAN_UP;

#include <ansi.h>;

int help(object me);

int main(object me, string arg)
{
        string msg;
        string name, id;

        if (! arg)
        {
                SHOP_D->list_shop(me);
                return 1;
        }
        
        switch (arg)
        {
        case "open"  :
                if (! SECURITY_D->valid_grant(me, "(wizard)"))
                        return notify_fail("你沒有權力使用店舖管理指令。\n");
                        
                SHOP_D->open_all(me); 
                break;
        case "close" :
                if (! SECURITY_D->valid_grant(me, "(wizard)"))
                        return notify_fail("你沒有權力使用店舖管理指令。\n");
                        
                SHOP_D->close_all(me); 
                break;
        case "reset" : 
                if (! SECURITY_D->valid_grant(me, "(wizard)"))
                        return notify_fail("你沒有權力使用店舖管理指令。\n");
                        
                SHOP_D->reset_all(me); 
                break;
        default :
                if (sscanf(arg, "open %s", name))
                {
                        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                                return notify_fail("你沒有權力使用店舖管理指令。\n");                        
                        SHOP_D->open_shop(me, name);
                        break;
                }
                if (sscanf(arg, "close %s", name))
                {
                        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                                return notify_fail("你沒有權力使用店舖管理指令。\n");                        
                        SHOP_D->close_shop(me, name);
                        break;
                }
                if (sscanf(arg, "reset %s", name))
                {
                        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                                return notify_fail("你沒有權力使用店舖管理指令。\n");                       
                        SHOP_D->reset_shop(me, name);
                        break;
                }
                if (sscanf(arg, "owner %s %s", name, id))
                {
                        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                                return notify_fail("你沒有權力使用店舖管理指令。\n");                        
                        SHOP_D->change_owner(me, name, id);
                        break;
                }
                else
                {
                        if( time()-query("last_tongshangbu", me)<2 )
                                return notify_fail("不要急，慢點，慢點咯！\n");

                        msg = SHOP_D->do_list_all(me, arg);

                        if (stringp(msg))
                                write(msg);

                        set("last_tongshangbu", time(), me);
                }
        }
        
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式：shop [物品英文名|物品中文名]
指令格式：shop [ open [店舖名稱] ]  | [ close [店舖名稱] ] |
               [ reset [店舖名稱] ] | [ owner <店舖名稱> <店主ID> ]

查看當前遊戲中的店舖經營狀況。

巫師可以用于管理店舖。使用 open 參數開放指定的一個店舖或
者所有店舖，使用close 參數將關閉指定的一個店舖或者所有店
舖，reset 參數重新初始化指定的一個店舖或者所有店舖。而使
用owner 參數則是設置店主的 id。

HELP);
        return 1;
}

