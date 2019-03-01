#include <ansi.h>

inherit ITEM;

#define DANSTORE_D         "/adm/daemons/danstored"

void create()
{
        set_name(NOR + YEL "桃木盒" NOR, ({ "taomu he", "taomu", "he" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "這是一個用桃木制成的盒子，可以用來存放丹藥，據說，凡是存放\n"
                                                      "在這個盒子裡的丹藥下線後都不會丟失。\n" HIG
                                                                          "指令格式：存儲丹藥：  store cun 數量 丹藥ID\n"
                                                                          "          取出丹藥：  store qu 數量 丹藥ID\n"
                                                                          "          查看盒子：  store show \n" NOR);
                set("value", 1);
                set("no_sell", 1);
                                set("no_give", 1);
                                set("no_drop", 1);

                        set("unit", "個");
        }

        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_store", "store");
}

int do_store(string arg)
{
        object me = this_player();
        string para, ob_id;
        int amount;

    // 先取下面具
    if (me->query_temp("apply/mask_flag"))
    {
         return notify_fail("閣下為何不以真面目示人？\n");
    }

        if (! arg)return notify_fail("\n未輸入參數或輸入參數錯誤。\n");

        if (arg == "show")
        {                
                DANSTORE_D->show_player_objects(me->query("id"));
                return 1;
        }

        // 查看所有倉庫用戶
        if (arg == "list")
        {
                if (! wizardp(me))return 0;
                DANSTORE_D->show_store_list();
                return 1;
        }
        // 查看其他玩家的存儲情況
        if (sscanf(arg, "show %s", para) == 1)
        {
                if (! wizardp(me))return notify_fail("\n輸入參數過多！\n");

                DANSTORE_D->show_player_objects(para);
                
                return 1;
        }

        if (sscanf(arg, "%s %d %s", para, amount, ob_id) != 3)
                return notify_fail("\n輸入參數錯誤 。\n");
        
        if (amount < 1)
                return notify_fail("\n輸入數量不能小于 1 。\n");

        if (para == "cun")
        {
                DANSTORE_D->store_player_objects(me, ob_id, amount);
                return 1;
        }
        if (para == "qu")
        {
                DANSTORE_D->get_player_objects(me, ob_id, amount);
                return 1;        
        }
        
        return notify_fail("\n輸入參數錯誤。\n");
}