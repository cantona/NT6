inherit ROOM;

#include <ansi.h>

int TEST_FLAG = 1;

public void set_test_flag(int n){TEST_FLAG = n;}

void create()
{
        set("short", HIR "祭壇" NOR);
        set("long",
"這裡是冰火島的中心，也是一處祭壇，這個祭壇沒有名字，但\n"
"從其建造的復雜度和氣勢來講，並不輸于嵩山的封禪台。祭壇四周\n"
"角落燃著藍色的火燄，正中擺放著一個巨大的香爐和祭台(jitai)。\n"
);

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("binghuo", 1);           // 表示在冰火島

        set("no_clean_up", 1);
        
        set("outdoors", "battle4");
       
        set("league_flag", "ALL_LEAGUE"); // 默認所有幫派都可以提前進入密道
        set("exits", ([ 
                "north"   : __DIR__"xuanwutai",
                "south"   : __DIR__"shenghuotai",
        ]));
        
        set("item_desc", ([ 
                "jitai"   :  HIC "祭台旁竟隱藏著一個奇怪的拉環，轉動(turn)拉環（lahuan）可能會開啟什麼機關。\n" NOR,
                "lahuan"  :  HIM "一個半圓形的拉環，古銅色，似乎連接著什麼機關。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_turn", "turn");
}

int do_turn(string arg)
{
        object me = this_player();
        object ob;
        
        if (! arg || arg != "lahuan")
                return notify_fail("你要轉動什麼東西！\n");
                
        if( query("exits/enter") )
                return notify_fail("密道入口已經開著了，你沒事吧？。。。\n");

        // 讀取幫戰控制文件，判斷是否密道開啟了，否則不能拉動拉環
        if( !BUNCH_D->is_battle_start() && !TEST_FLAG )
                return notify_fail("你使勁轉動拉環，似乎沒有什麼作用。\n");
                
        // 金毛獅王存在則不能開啟
        if (objectp(ob = present("jinmao shiwang", this_object())))
        {
                message_vision(HIM "一陣光芒閃過，" + ob->name() + HIM "攔在$N" HIM "面前，喝道：”哼，先過了我這關再說！“\n" NOR, me);
                return 1;
        }

        write("你使勁轉動拉環，只聽一聲悶響，祭壇微微顫動，祭壇後竟露出一條通道(enter)。\n" NOR);
        tell_room(this_object(), HIC + me->name() + HIC "使勁轉動拉環，只聽一聲悶響，祭壇微微顫動，祭壇後竟露出一條通道(enter)。\n" NOR, ({me}));

        set("exits/enter", __DIR__"st0");
        
        remove_call_out("close_out");   
        call_out("close_out", 300);
        
        me->start_busy(2);
        
        return 1;
}

void close_out()
{
        delete("exits/enter");  
        tell_room(this_object(), HIC "一聲悶響，祭壇微微顫動，似乎是密道關閉了。\n" NOR, ({}));
}


// 呼叫來自 金毛獅王死亡後 ,league代表幫派名，如果為"ALL_LEAGUE"表示任何幫派都可以進入
public set_flag(string league)
{
        set("league_flag", league);
        remove_call_out("clear_league_flag");
        call_out("clear_league_flag", 60, league);
        
        if (league != "ALL_LEAGUE")
                tell_room(this_object(), HIM "現在只有【" + league + HIM "】可以提前一分鐘進入密道！\n" NOR, ({}));
}
void clear_league_flag(string league)
{
        set("league_flag", "ALL_LEAGUE");
        
        if (league != "ALL_LEAGUE")     
                tell_room(this_object(), HIG "其他幫派可以進入密道了！\n" NOR, ({}));
}

int valid_leave(object me, string dir)
{
        
        if (dir == "enter")
        {
                // 非幫戰不能進入
                if( !BUNCH_D->is_battle_start() && !TEST_FLAG )
                        return notify_fail("現在不是幫戰期間，不能進入密道！\n");
                
                // 金毛獅王未死亡的標志不能進入
                if (present("xie xun", this_object()))
                        return notify_fail("金毛獅王守護著祭壇密道，不能進入！\n" NOR);
                
                // 如有幫派優先標志，標志不是ALL_LEAGUE，我不是標志指示幫派，則標志存在時不能進入
                if( query("league_flag") != "ALL_LEAGUE" && query("bunch/bunch_name", me) != query("league_flag") && !TEST_FLAG )
                        return notify_fail("你現在暫時不能進入，還是稍微等等吧！\n");
        }
        
        return ::valid_leave(me, dir);
}
