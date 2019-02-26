// Room: /xiakedao/shidong2.c

inherit ROOM;

#include <ansi.h>

string look_bi();

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，四周點着八盞油燈，使得整個房間非常明
亮。山洞四周石壁(bi)上像是刻畫着什麼東西，你禁不住想看
看。
LONG );
        set("exits", ([
                "east" : __DIR__"shidong3",
                "west" : __FILE__,
                "south" : __FILE__,
                "north" : __DIR__"yingbin",
        ]));

        set("item_desc",([
                "bi"  : (: look_bi :),
        ]));
        set("coor/x", -3080);
        set("coor/y", -22090);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_think", "think");
}

string look_bi()
{
        object me = this_player();
        string msg;

        if( me->query_skill("literate", 1)
                 || query("learned_literate", me)){
                msg = HIW "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁佈滿\n"
                        "蝌蚪形狀的文字。你仔細推敲這些文字卻一無所獲。\n" NOR;
        } else {
                msg = HIW "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁佈滿\n"
                        "蝌蚪形狀的文字，由於你從未讀過書，所以你並沒有在\n"
                        "意那些文字。你猛然看到文字下面有很多圖畫，是用利\n"
                        "器所刻，上面畫着各式各樣的人物，卻都全身裸露，但\n"
                        "可見其全身各處經絡及經絡走向。你越想越離奇，感覺\n"
                        "全身各處經脈微微顫動，禁不住自己想要跟着圖中所刻\n"
                        "的經絡走向學(think)起來。\n" NOR;
        }

        return msg;
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

        if( query("special_skill/clever", me) )
                add = me->query_int() / 4;
        else
                add = me->query_int() / 10;

        if (! living(me) || arg != "bi")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙着呢。\n");

        if( me->query_skill("literate",1) || query("learned_literate", me) )
                return notify_fail("你發現石壁上的武功深奧之極，一時難以體會！\n");

        if( query("int", me)<27 )
                return notify_fail("你若有所悟，然而總是有點不明白。\n");

        if( query("dex", me)<27 )
                return notify_fail("你研究了半天，只覺招式始終無法隨意施展。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本內功火候不夠，無法領悟石壁"
                                   "上的武功。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，無法學習石壁上的武功。\n");

        if( query("jing", me)<85 )
                return notify_fail("你現在精神不濟，過於疲倦，還是休息"
                                   "一會吧。\n");

        if ((int)me->query_skill("taixuan-gong", 1) >= 60)
                return notify_fail("你覺得石壁上記載的武功對你來説太淺了，結果你"
                                   "什麼也沒學到。\n");

        me->receive_damage("jing", 75);

        if (me->can_improve_skill("taixuan-gong"))
                me->improve_skill("taixuan-gong", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳牆上所記載的神功，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「太玄功」有了新的領悟。\n" NOR);
        return 1;
}