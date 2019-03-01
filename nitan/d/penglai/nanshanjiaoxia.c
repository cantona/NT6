inherit ROOM;

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"

void create()
{
        set("short", "南山腳下");
        set("long",@LONG
這是通往蓬萊島南山的必經之路，傳說南山乃仙人修煉仙法的
地方，屬于禁地。雖無人看守，但若沒有仙人的指引外人是無論如
何也無法進入的。四周植物蔥鬱，仙氣圍繞，景致甚是迷人。抬頭
仰望南山，山峰高聳，仙氣繚繞，再一細看又若隱若現，令人難以
琢磨。
LONG);

        set("exits", ([
                "north"    : __DIR__"xianrenzhilu",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);
        
        setup();
}

void init ()
{
        add_action("do_closeeye", "closeeye");
        
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
        
        if (! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n你正欲進入南山，卻發現這裡根本沒有上山之路，奇哉！。\n" NOR);
        }
        else
        {
                tell_object(this_player(), HIG "\n要進入南山，閉上你的眼睛(closeeye)，默念守路仙人教給你的咒語。\n" NOR);
        }
}

int do_closeeye(string arg)
{
        object me;
        int i;
        object *inv;
        object horse, person;
        
        
        me = this_player();
        
        if (me->is_busy())
                return notify_fail("你正忙。\n");
                
        // 所有騎馬的人必須下馬
        if (objectp(horse = me->query_temp("is_riding")))
        {
                if (objectp(person = horse->query_temp("is_rided_follow")))
                        person->delete_temp("is_riding_follow");

                horse->delete_temp("is_rided_follow");
                horse->delete_temp("is_rided_by");
                me->delete_temp("is_riding_follow");
                me->delete_temp("is_riding"); 

                message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎受到了驚嚇，前蹄一揚，所有人"
                               "被迫跳下馬。\n\n" NOR, me);

                return 1;
        }
                        
        // 把背起的用戶放下來
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人背起的用戶
                inv[i]->move(__FILE__);                
        }

        if (this_player()->query("penglai/nanshan_quest/ok"))
        {
                i = 20;
                tell_object(this_player(), HIG "\n你閉上你的眼睛，默念守路仙人教給你的咒語...\n" NOR);
                if (! MEMBER_D->is_valib_member(this_player()->query("id")))
                        return notify_fail("對不起，南山地圖只對有效會員開放。\n");
                        
                me->move(__DIR__"nanshanzhong" + random(i));
        }
        else
        {
                return 0;
        }

        return 1;
}