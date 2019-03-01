inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "山崖");
        set("long", @LONG
此處入雲高聳，已是黑木崖上，兩旁站滿了日月神教的弟子。兩
旁的刻著兩行大字，右首是「文成武德」，左首是「仁義英明」，橫
額上刻著「日月光明」四個大紅字。崖邊卷著幾捆碗口粗的繩鎖，繩
索的一端系有一個吊籃(basket)。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "north" : __DIR__"shanya2",
        ]));
        set("objects", ([
                __DIR__"npc/dizi2" : 4,
        ]));
        set("item_desc", ([
                "basket" : "一個掉巨大的吊籃，是供給日月神教中人下山之用。\n"
        ]) );
        setup();
}
  
void init()
{
        add_action("do_enter", "enter");
        add_action("do_float", "float");
        add_action("do_float", "piao");
}

int do_enter(string arg)
{
        object me, myenv;
        me = this_player();

        if (! arg || arg != "basket" )
                return notify_fail("什麼？\n");

        if( query("family/family_name", me) != "日月神教" )
                return notify_fail(CYN "日月弟子道瞟了你一眼，冷笑一聲，轉過頭"
                                   "去，對你理也不理。\n" NOR);

        message_vision(HIY "\n$N" HIY "穩穩當當跨進吊籃，向日月弟子打個手勢。那"
                       "弟子點了點頭，將\n開關一扳，放開繩索，吊籃頓時緩緩向下滑"
                       "去。\n\n", me);
        myenv = environment(me);
        me->move (__DIR__"basket");
        me->start_call_out((: call_other, __FILE__, "down1", me :), 3);
        return 1;
}

void down1(object me)
{
        tell_object(me, HIW "\n你乘座的吊籃急速下降，籃外的朵朵白雲向上沖去。\n\n" NOR);
        me->start_call_out((: call_other, __FILE__, "down2", me :), 3);
}

void down2(object me)
{
        tell_object(me, HIG "\n霎時間，一片遼闊的草坪出現在你面前。\n\n" NOR);
        me->move(__DIR__"up1");
        message_vision(HIC "\n$N" HIC "乘坐吊籃從黑木崖上滑了下來。\n\n" NOR, me);
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("juechen-shenfa", 1) < 180)
        {
                message_vision("$N朝山崖下望去，沉思良久，嘆了口氣。\n", me);
                return 1;
        }

        if( query("neili", me)<100 )
        {
                tell_object(me, "你的內力不夠，還是休息一下再說吧。\n");
                return 1;
        }

        addn("neili", -80, me);

        message_sort(HIC "\n$N" HIC "深深納入一口氣，身形飄然而起，朝山"
                     "崖下落去。\n\n" NOR, me);
        me->move(__DIR__"up1");
        tell_object(me, "你飄然落至黑木崖山腳之下。\n");
        message("vision", HIC "\n忽聽一聲清嘯由遠及近，" + me->name() +
                          HIC "從上面的山崖飄然落下。\n" NOR,
                          environment(me), ({ me }));
        return 1;
}
