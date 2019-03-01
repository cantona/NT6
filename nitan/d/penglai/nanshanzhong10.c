inherit DEMONROOM;

#include <ansi.h>

int i = 20;

void create()
{
        set("short", "南山中");
        set("long",@LONG
這裡是蓬萊仙島仙者修煉仙法的地方，傳說南山本不存在，乃
是眾仙施法而變成。四周仙氣大盛，原本以為南山與普通高山無異，
卻不知這裡的奇幻之處。一旦進如南山之中，唯一的出路就是回到
山腳下，你站立良久才發現，所在之處並非一成不變，隨著仙氣地
流動，時高時低，時隱時現。有時你除了四周的仙氣什麼都看不見，
有時卻隨著此處的升高，竟可以望見東方的麒麟崖。據說，當四周
環境隨著仙氣不斷變化的時候，可以找到去南山之顛的路，運氣好
的話還會發現傳說中的七仙女台和飛馬崖。
LONG);

        set("exits", ([
                "xunlu"    : __DIR__"nanshanzhong0",
                "out"      : __DIR__"nanshanjiaoxia",
        ]));
        
        // 南山之顛
        if (random(20) == 1)
                add("exits", ([ "nanshanzhidian" :  __DIR__"nanshanzhidian",]));
        
        // 七仙女台和飛馬崖
        if (random(10) == 1)
                add("exits", ([ "qixiannvtai" :__DIR__"qixiannvtai",]));
        if (random(10) == 1)
                add("exits", ([ "feimaya" : __DIR__"feimaya",]));

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 60); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/nianshou");
        
        setup();
}

void init ()
{
        add_action("do_xunlu", "xunlu");
        
        if (! this_player()->query("penglai/go_quest/ok"))
        {
                this_player()->start_busy(3);
                tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);
        }
        else
        {
                if (random(2))
                {
                        this_player()->start_busy(1);
                        tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);                
                }
        }        
}

int do_xunlu()
{
        object me;
        
        me = this_player();
        
        if (me->is_busy())return notify_fail("你正忙。\n");
        
        tell_object(this_player(), HIG "\n你在南山中四處走動尋找新的道路 ...\n\n" NOR);

        me->move(__DIR__"nanshanzhong" + random(i));

        return 1;
}