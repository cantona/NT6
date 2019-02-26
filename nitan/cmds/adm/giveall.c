// giveall.c

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count;
        string target, gift_file, str;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail("giftall 派禮物給在線玩家，命令格式： giftall </路徑/../目標文件名> <數量>\n\n");

        if (sscanf(arg, "%s %d", target, count) != 2)
                target = arg;

        if (sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target;

        if (file_size(gift_file) == -1)
                return notify_fail("路徑不正確，無法找到物品。\n");

        seteuid(getuid());

        foreach(object player in users())
        {
                ob = new(target);

                if( count>1 && query("base_unit", ob) )
                        ob->set_amount(count);

                ob -> move(player);

                tell_object(player, HIW "\n\n忽然從極高極遠的天空中極速降下一隻渾身烈焰的"HIR"火鳳"HIW"，周身閃耀七彩光芒。\n" NOR);
                tell_object(player, HIC "它爪下似乎抓着什麼東西，突然"HIC"火鳳"HIW"鬆開腳爪，有個東西直向你掉落下來。\n" NOR);
                tell_object(player, HIG "你猛一提氣縱身一躍丈高將此物抓在手中，又瀟灑的飄落地面。\n\n" NOR);

        }
        str=sprintf("共有%d位玩家得到了%s。\n\n",sizeof(users()),query("name", get_object(target)));
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：giveall 物品路徑

給在線的所有玩家一件物品。
HELP
        );
        return 1;
}
