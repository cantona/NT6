// Room: /d/tangmen/dating.c
//by hem
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "議事大廳");
        set("long", @LONG
        這裏是唐門的議事大廳。平時一般不使用，只有在唐門發生重大事情的時
候，唐門的長輩才在這兒聚集商量。整個大廳建築得很奇怪，四周有八根硃紅大柱
地面黝黑髮亮，是唐門平時冶煉暗器所剩的鐵屑溶製成的整塊。正中是一個很大的
八卦圖(bagua)。
LONG
        );
        
        set("valid_startroom", 1);

        set("exits", ([
                
           "north" : __DIR__"houzhai",
        ]));
     set("objects", ([
 __DIR__"npc/dizi" : 1,
                        ]));

        set("item_desc", ([
                "bagua" : HIY "很奇怪的八卦圖，不知道唐門為什麼要在這兒刻上它。\n",  
    ]));

        setup();

}
void init()
{
        add_action("do_break", "break");
}
int do_break(string arg)
{
    int n;
        object me = this_player();

    if( !arg || arg!="bagua" )
        {
        write("唐門的財物豈是你隨便能破壞的！\n");
        return 1;
    }
if( query_temp("marks/鬧", this_player())){
    message_vision(
    "$N走到八卦前，騰身而起，運起全身內力，雙掌自上而下重重擊向八卦。\n", this_player());


    n=query("neili", me);
    if (n >= 1500)
        {
        message_vision(
        HIR"$N只聽轟得一聲巨響！！！八卦竟然翻轉，面前出現一個洞。\n"NOR, this_player());
        set("exits/down", "/d/tangmen/qiushi");
        set("neili", n-1500, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else
        {
                message_vision(
                HIW"結果只聽一聲悶哼，$N被八卦的反彈力震得眼前一黑....\n"NOR, this_player());
set("neili", 0,                 this_player());
                this_player()->unconcious();
    }
delete_temp("marks/鬧", me);
return 1;    
}
else 
        {write(HIY"你娃腦殼有包啊？看到是鐵砣砣都要去打！\n"NOR);
        return 1;}
}

void close(object room)
{
    message("vision","只聽見一陣嘎嘎的響聲，八卦又翻了轉來，恢復了原樣。\n", room);
    delete("exits/down", room);
}