#include <ansi.h> 

inherit ROOM;

void create()
{
        set("short", HIR "拇指峰" NOR);
        set("long", @LONG
拇指峰是鐵掌五峰中最為低矮的一峰，名為峰，實則只是一座較高的石
山罷了。峰頂四周全是又大又圓的巖石，在日曬雨淋下，被風蝕得十分之光
滑。在巖石的縫隙中，長出許多鬆樹，其中一棵尤其引人注目。相傳這棵鬆
名曰──並蒂鬆(song)，乃同根而生，于距地一米高處，忽分為二。這兩根
樹幹同粗同高，均長得高大挺拔，枝葉茂盛，尤如兄弟一般，因此又名為兄
弟鬆。
LONG    );
        set("exits", ([
                "southdown" : __DIR__"sslu-3",
        ]));

        set("item_desc", ([ 
                "song" : GRN "\n這棵鬆樹能長得如此奇特，必蘊涵了天地日月之精華。\n" NOR,
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_caiqi", "caiqi");
}

int do_caiqi(string arg)
{
        mapping fam;
        object me;
        me = this_player();

        if ( ! living(me)) return 0;
        if ( ! living(this_player()) || arg != "song" )
        {
                message_vision("你想幹什麼？\n",me);
                return 1;
        }

        if( me->is_busy() )
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("force",1) > 100)
                return notify_fail("依照你的內功修為已經再無法從樹中吸取任何東西了！\n");

        if ((int)me->query_skill("force", 1) < 30 )
                return notify_fail("你的內功修為太低了，沒辦法從樹中採氣！\n");

        if (! me->can_improve_skill("force"))
                return notify_fail("你的實戰經驗不夠，無法再加深你的內功！\n");

        if( query("jing", me)<40 )
        {
                write("你忽然覺得精神不濟，無法控制體內的真氣！\n");
                return 1;
        }

        me->receive_damage("jing", 30);
        message_vision(HIW "$N" HIW "閉上雙眼，雙手緊緊地貼住樹幹，開始緩緩吐吶練功。\n" NOR, me);
        me->improve_skill("force",query("con", me)*2/3);
        me->start_busy(random(2));
        return 1;
}