#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIC "練功房" NOR);
        set("long", @LONG
這是一間用花崗巖砌成的石屋。室內一隻大爐中燃了洪炭，煮着熱氣騰
騰的一鑊 (huo)東西，鑊旁兩個黑衣小童，一個使勁推拉風箱，另一個用鐵
鏟翻炒鑊中之物，聽這沙沙之聲，所炒的似是鐵沙。幾名幫中弟子閉目盤膝
坐在鍋前，或對着騰上的熱氣吐吶，或把手掌插入(charu)鑊中苦練掌法。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"guangchang",
        ]));

        set("objects",([
                __DIR__"npc/heiyi" : 1,
        ]));

        set("item_desc", ([
                "huo" : HIR "\n這是一口巨大的鐵鍋，鍋中盛滿鐵沙，下面燃着炭火。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_cha", "charu");
}

int do_cha(string arg)
{       
        mapping fam;
        object me;
        me = this_player();

        if ( ! living(me)) return 0;
        if ( ! living(this_player()) || arg != "huo" )
        {
                write("你想往哪兒插呀！\n");
                return 1;
        }

        if( me->is_busy() )
                return notify_fail("你現在正忙着呢。\n");

        if ( (int)me->query_skill("strike", 1) < 30 )
                return notify_fail("你將雙手插入鑊中，灼熱的鐵沙登時燙得你怪叫不止，看來還是吧掌法練高點再來吧。\n");

        if ( (int)me->query_skill("strike", 1) > 100)
                return notify_fail("你將雙手插入鑊中，發現用鐵沙練習已絲毫提高不了你的掌法了。\n");

        if (! me->can_improve_skill("strike"))
                return notify_fail("你的實戰經驗不夠，無法再加深你的掌法！\n");

        if( query("qi", me)<40 )
        {
                write("你覺得一股熱氣直逼上來，焦燥難當。還是休息一下再接着練吧！\n");
                return 1;
        }

        me->receive_damage("qi", 30);
        me->improve_skill("strike",query("con", me)*2);
        me->start_busy(random(2));
        message_vision(HIR "\n$N" HIR "將雙手插進鑊中的鐵沙裏。\n" NOR, me);
        write(RED "灼熱的鐵沙將你的雙手燙得通紅，你覺得雙手登時變得更加強壯有力了。\n" NOR);
        return 1;
}