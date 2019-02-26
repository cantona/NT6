#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(HIB"副本傳送門"NOR, ({ "fuben door", "door" }) );
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB"目前的功能有：\n"+
                            "enter <迷宮代碼>：創建一個屬於自己或隊伍的迷宮副本。\n"
                            "迷宮代碼：forest-原始森林，jiutoushe-九頭蛇領域，desert-無盡大漠，necropolis-詭異墓園，temple-失落神廟，mausoleum-秦皇陵墓。\n"
                            "\n"NOR); 
                set("unit", "個");
                set("no_get",1);
                set("value", 20);
        }
        setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg) 
{
        int valid;
                
        if( !arg || arg == "" )
                return 0;
        
        valid = FUBEN_D->valid_enter(this_player(), arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(this_player(), arg);
        else {
                if( valid == 0 )
                        write("您實戰經驗不足，進副本恐有不測，還是先歷練一下再來吧。\n");
                else if( valid == -1 )
                        write("您經驗太高了，就不要進去欺負那些可憐的小怪物了吧。\n");
                else if( valid == -2 )
                        write("遊戲中目前並沒有開放該副本，請您核對後再試。\n");
                else if( valid == -3 )
                        write("該副本限制IP多重進入，您已經超過最高上限。\n");
                else if( valid == -4 )
                        write("該副本被巫師關閉，您暫時無法進入。\n");
                else if( valid == -5 )
                        write("你離上次進入副本時間太短，請休息會再來。\n");
                else if( valid == -6 )
                        write("該副本必須組隊才能進入。\n");
                else if( valid == -7 )
                        write("你的隊伍人數超過該副本規定的上限。\n");
                else if( valid == -8 )
                        write("該副本是單人副本，您必須解散隊伍方可進入。\n");
        }        
        return 1;
}
