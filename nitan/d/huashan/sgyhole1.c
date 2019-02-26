// sgyhole1.c
// By Hop, 97.04.30
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
山洞內有塊光溜溜的大石，不知道曾有多少華山派的前輩在此思
過面壁，以致這塊大石竟被坐得滑溜。石壁(wall)左側刻着「風清揚
」三個大字，是以利器所刻，筆劃蒼勁，深有半寸。這三字刻得勁力
非凡，想必其人武功一定十分了得。
LONG );
        set("objects", ([
                CLASS_D("huashan")+"/linghu" : 1,
        ]));
        set("exits", ([ /* sizeof() == 2 */
            "out" : __DIR__"siguoya",
        ]));
        set("item_desc", ([
            "wall" : "一面很厚的石壁。\n"
        ]) );
        setup();
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        int n;
        object weapon,me=this_player();
        mapping fam;

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你一掌打在石壁，滿手都是鮮血。\n");

        message_vision(HIC "$N走到石壁前，拿起" + weapon->name() + "，隨手向石壁刺了過去！\n"NOR, me);

        if( query("neili", me)<200 )
        {
                message_vision(HIC "結果只聽一聲悶哼，$N被石壁的反彈力震得眼前一黑....\n" NOR,
                               me);
                set("neili", 0, me);
                me->unconcious();
                return 1;
        }

        message_vision(HIC "$N只聽一聲轟響，石壁竟然被捅穿了，原來裏面有一個大洞！\n"NOR, me);
        set("exits/enter",__DIR__"sgyhole");
        addn("neili", -200, me);
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close_out()
{
        if (query("exits/enter")) delete("exits/enter");
}

void close(object room)
{
        message("vision","崖上忽然掉下來一塊巨石，將洞口封了個嚴嚴實實。\n", room);
        delete("exits/enter", room);
}