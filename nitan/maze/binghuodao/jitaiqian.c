inherit ROOM;

#include <ansi.h>

int TEST_FLAG = 0;

public void set_test_flag(int n){TEST_FLAG = n;}

void create()
{
        set("short", HIY "祭台前" NOR);
        set("long",@LONG
這是一處寬闊的洞穴，明亮開朗。洞穴四周插滿了各種旗
幟，石壁上也掛有各種祭祀的牲口，但早已化為白骨。洞穴正
中擺放著一個玉石做成的祭台（jitai）， 上面插著一面鮮紅
的旗幟。
LONG);

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("binghuo", 1);           // 表示在冰火島


        set("no_clean_up", 1);
        
        set("exits", ([ 
                "out"     : __DIR__"jitan",
        ]));
        
        set("item_desc", ([ 
                "jitai"   :  HIC "這是一個廢棄的祭台，似乎進行過大型祭祀，似乎可以跳上(jump jitai)祭台。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "jitai")
                return notify_fail("你要往哪裡跳。\n");
                
        // 有隱身符或保護的不增加幫派時間
        if( query_temp("apply/invisible", me) )
        {
                tell_object(me, HIG "你處于隱身狀態，不能上祭台！\n" NOR);
                return 1;
        }
        if (me->query_condition("die_guard"))
        {
                tell_object(me, HIG "你處于被保護狀態，不能上祭台！\n" NOR);
                return 1;
        }
        
        if( query("age", me) < 5 && query("reborn/times", me) )
        {
                tell_object(me, HIG "你處于被保護狀態，不能上祭台！\n" NOR);
                return 1;
        }

        message_vision(HIC "$N縱身一躍，跳上祭台！\n" NOR, me);

        me->move(__DIR__"jitai");
        
        return 1;
}
