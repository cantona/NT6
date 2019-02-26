// Room: /d/baihuagu/huagu7.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", RED"百花谷"NOR);
        set("long", 
HIC"又轉了幾個彎，迎面兩面山壁夾峙三株大松樹沖天而起，擋在
山壁間。成為兩道天然的屏障。\n"NOR);
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"huagu6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -360);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_swear","swear");
        add_action("do_swear","han");
        add_action("do_swear","huhan");
}
int do_swear(string arg)
{
        if( !arg) return 0;
        if( arg == "老頑童" ) 
        {
                message_vision(HIG "$N朗聲喊道：老頑童，小朋友來找你玩兒啦！！！\n"NOR, this_player());
                message_vision(HIY "只聽見裏面呵呵的笑聲傳來：又有人來找我玩兒了，快進快進！\n"NOR, this_player() );
                call_out("close_passage", 10);
                set("exits/enter", __DIR__"baihuagu");
                return 1;
        }
        else
        {
                message_vision(HIG"$N朗聲高喊：“"+arg+"！！！”空谷迴音，長久不絕。\n"NOR, this_player());
                return 1;
        }
}

void close_passage()
{
        object room;
        if( !query("exits/enter") ) return;
        delete("exits/enter");
}