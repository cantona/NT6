inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "長生村");
        set("long",@LONG
這裡是長生村南村，周圍三三兩兩的茅草房，雞犬相聞，
炊煙了了，不時有幾只黃毛狗搖著尾巴對著你叫幾聲，看來
在對你表示歡迎。不遠處幾位村民正在耕田，耕牛傳來賣力
的吼叫聲。一群幼雞跟著一名農婦，正在爭搶著農婦洒下的
米食。偶有三五成群的小毛孩相互追逐，嬉戲。此情此景，
令人好生羨慕。
LONG);

        set("exits", ([
                "south"         : __DIR__"changshengcunsouth2",
                "north"         : __DIR__"changshengcun",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);
        set("no_fight", 1);
        set("sleep_room", 1);

        set("objects", ([
                __DIR__"npc/wantong" : random(4),
                __DIR__"npc/nongfu1" : random(2),
                __DIR__"npc/nongfu2" : random(2),
        ]));
        
        setup();
}

void init ()
{
        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
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
}