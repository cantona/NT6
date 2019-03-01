#include <ansi.h> 

inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這裡是苗人鳳的書房，房間內整整齊齊的堆放著各類書籍。
書房的中央橫放著一張案台，案台上擺著幾本攤開的書冊，旁
邊還有未燃盡的蠟燭，似乎苗人鳳常在這裡挑燈夜讀。牆壁上
懸掛著幾幅圖(tu)畫，像是出自苗人鳳本人的手筆。
LONG);
        set("exits", ([
                  "north" : __DIR__"miaojia_houting",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "tu" : HIC "\n只見圖畫中繪著一些正在打鬥的小人，似是"
                       "與掌法有關。\n" NOR,
        ]) );
        set("coor/x", -8990);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_think", "think");
        add_action("do_canwu", "canwu");
}

int do_think(string arg)
{
        object me;
        object weapon;
        me = this_player();

        if ( ! living(me)) return 0;

        if ( ! living(this_player()) || arg != "tu" )
                return notify_fail("你要幹什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("strike", 1) < 30 ||
           (int)me->query_skill("chongtian-zhang", 1) < 30)
                return notify_fail("你發現圖中所記載的掌法過于高深，自"
                                   "己無法領會到任何東西。\n");

        if ((int)me->query_skill("strike", 1) > 149 &&
           (int)me->query_skill("chongtian-zhang", 1) > 149)
                return notify_fail("你發現圖中所記載的掌法過于膚淺，自"
                                   "己無法領會到任何東西。\n");

        if( query("jing", me)<50 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 30);

        if ((int)me->query_skill("strike", 1) < 150 &&
           me->can_improve_skill("strike"))
                me->improve_skill("strike",query("int", me)*3/2);

        if ((int)me->query_skill("chongtian-zhang", 1) < 150 &&
           me->can_improve_skill("chongtian-zhang"))
                me->improve_skill("chongtian-zhang",query("int", me)*3/2);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳圖中所記載的掌法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「基本掌法」和「白鶴沖天掌」有了新的領悟。\n" NOR);
        return 1;
}

int do_canwu(string arg)
{
        object me = this_player();
        object ob;
        object ob1;

        if (arg != "wall" && arg != "shu")
                return notify_fail("你要參悟什麼？\n");

        if( query("can_perform/panlong-zhao/tan", me) )
                return notify_fail(WHT "你隨手翻閱案台上的書籍，發現上"
                                   "面已經沒什麼東西值得研究了。\n" NOR);

        if (! (int)me->query_skill("panlong-zhao"))
                return notify_fail(WHT "你隨手翻閱案台上的書籍，發現書"
                                   "中所記載的東西和你所習的武學沒什麼"
                                   "瓜葛，參悟不出什麼。\n" NOR);

        if ((int)me->query_skill("panlong-zhao", 1) < 130)
                return notify_fail(WHT "你隨手翻閱案台上的書籍，發現書"
                                   "中所記載的爪法甚是精妙，可卻是太過"
                                   "深奧，自己一時無法領悟。\n" NOR);

        if (me->is_busy())
                return notify_fail("你現在正在參悟中。\n");

        if( query("potential", me)<query("learned_points", me)+10 )
                return notify_fail("你的潛能不夠了，參悟不出什麼。\n");

        if( query("jing", me)<30 )
                return notify_fail("你太疲倦了，休息一下吧。\n");

        if (random(20) < 18)
        {
                me->receive_damage("jing", 25);
                addn("learned_points", 10, me);
                me->start_busy(2);
                message_vision(WHT "$N" WHT "仔細翻看案台上的諸多書籍"
                               "，閱讀其中每個細節。\n" NOR, me);
                tell_object(me, HIY "你對越空盤龍爪有了更深的理解，但"
                               "尚需進一步的參悟。\n" NOR);
                return 1;
        } else
        { 
                me->receive_damage("jing", 25);
                addn("learned_points", 10, me);
                me->start_busy(2);
                message_vision(WHT "$N" WHT "仔細翻看案台上的諸多書籍"
                               "，閱讀其中每個細節。\n" NOR, me);

                tell_object(me, HIY "過得良久，陡然間你雙目一亮，終于"
                                "領悟了書中記載越空盤\n龍爪「雲中探爪"
                                "」絕技的奧秘！\n" NOR + HIC "你學會了"
                                "「雲中探爪」。\n" NOR);
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 1500000);
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 1500000);
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 1500000);
                if (me->can_improve_skill("panlong-zhao"))
                        me->improve_skill("panlong-zhao", 1500000);
                if (me->can_improve_skill("panlong-zhao"))
                        me->improve_skill("panlong-zhao", 1500000);
                if (me->can_improve_skill("panlong-zhao"))
                        me->improve_skill("panlong-zhao", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                set("can_perform/panlong-zhao/tan", 1, me);
        }

        return 1;
}