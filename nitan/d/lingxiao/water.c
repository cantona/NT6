#include <ansi.h>

inherit ROOM;

void create()
{
   set("short", "雪山温泉");
   set("long", @LONG
這是兩個山道盆地之間的一處温泉(quan)，一股噴泉正在嘶
嘶噴水，灼熱的水花被風吹散，在月光下形成一團團白色的花環。
在這雪山之上，居然還有此等令人愜意之處，亦不由讓人感歎造
物之神奇。碧波綠水中，飄蕩着朵朵雪蓮花瓣，片片雪花飄然而
下，離水面有數寸，便即紛紛化為白霧而散。在這生命絕跡的大
雪山之上，惟有這裏，才有綠樹、紅花、青草。一個少女在温泉
畔凝望落花，似有無限心事。
LONG);
        set("outdoors", "lingxiao"); 
            set("resource/water", 1);
            set("objects", ([
                   __DIR__"npc/a-xiu" : 1,
            ]) );
        set("exits", ([ 
                     "east" :__DIR__"sroad6",
        ]));
        set("item_desc", ([
                "quan" : HIC "這是山道間的一處温泉，深不見底，似乎可以"
                         "潛(dive)下去。\n" NOR,
        ]) );
        setup(); 
}

void init()
{       
        add_action("do_dive", "dive");
}

int do_dive(string arg)
{
        object me = this_player();

        if ((arg != "quan" || ! arg))
                return notify_fail("你要潛什麼？\n");

                   message_vision(HIY "只見$N" HIY "憋足了一口氣，“撲通”一"
                               "聲，縱身跳下了温泉。\n" NOR, me);

        if ((int)me->query_skill("force") < 100)
        { 
                   message_vision(HIR "$N" HIY "剛下水不久，發現愈往下潛，水"
                               "壓愈大，再也忍受不住，猛地竄了上來。\n"
                               NOR, me);
        } else 
        {
                message_vision(HIY "$N" HIY "只覺壓力越來越大，立即強運內"
                               "力，奮力支持，繼續向下潛去……\n\n" NOR +
                               HIC "只聽水中嘩啦一聲，就平靜下來了。\n" NOR,
                               this_player()); 
                me->move(__DIR__"wave1"); 
        } 
        return 1;
}
