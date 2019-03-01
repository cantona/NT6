#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(HIG"原始森林入口"NOR, ({ "forest door","door"}) );
        set_weight(5);
        set("no_get",1);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", GRN"從這個入口可以進入原始森林迷宮副本。(enter door)\n"NOR); 
                set("unit", "個");
                set("lore",1);
                set("value", 20);
        }
        setup();
}
void init()
{
        add_action("do_enter","enter");
}

/*
int do_enter(string arg) {
        if (arg!="door")
                return 0;

        MAZE_D->enter_virtual_maze(this_player(), "forest");
        return 1;
}
*/

int do_enter(string arg) 
{
        int valid;
                
        if( !arg || (arg != "door" && arg != "forest") )
                return 0;
        
        arg = "forest";
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

        }        
        return 1;
}


