inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "長生梅林");
        set("long",@LONG
此處是蓬萊仙島的梅林，由於離長生村很近，所以取命
為長生梅林。走到這裏，梅花的撲鼻之香早已浸透全身各處
令人身心舒暢無比。據説，這裏的梅花每隔一段時間會掉落
在地上，有些梅花吸收了這裏的仙氣便會逐漸成長，最終變
成一種叫青梅的果實。而用青梅加上其他材料釀成的青梅酒
乃是人間絕對品嚐不到的。
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin2",
                "east"         : __DIR__"changshengdao1",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        
        set("n_time", 20); 
        set("n_npc", 2); 
        set("n_max_npc", 10);
        set("s_npc", __DIR__"npc/xique");
                
        if (random(2) == 1)
        {
                if (random(2) == 1)
                        set("objects", ([
                                __DIR__"obj/meihua" : 1 + random(3),
                        ]));
                else
                        set("objects", ([
                                __DIR__"obj/qingmei" : 1 + random(4),
                        ]));                        
        }
        
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