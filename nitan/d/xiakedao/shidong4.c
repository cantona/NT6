// Room: /xiakedao/shidong4.c

inherit ROOM;

#include <ansi.h>

string look_bi();

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，四周點著八盞油燈，使得整個房間非常明
亮。山洞四周石壁(bi)上像是刻畫著什麼東西，你禁不住想看
看。
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"shidong5",
                "south" : __FILE__,
                "north" : __DIR__"yingbin",
        ]));

        set("item_desc",([
                "bi"  : (: look_bi :),
        ]));
        set("coor/x", -3070);
        set("coor/y", -22100);
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
                msg = HIC "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁布滿\n"
                        "蝌蚪形狀的文字。你仔細推敲這些文字卻一無所獲。\n" NOR;
        } else {
                msg = HIC "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁布滿\n"
                        "蝌蚪形狀的文字，由于你從未讀過書，所以你並沒有在\n"
                        "意那些文字。你猛然看到文字下面有很多圖畫，是用利\n"
                        "器所刻。上面畫著各式各樣的人物，有的站成馬步，有\n"
                        "的手成掌狀，劈空而出……  但是上面人物卻仍舊裸露\n"
                        "全身，其周身經脈走向清晰無比，配合著各種招式，更\n"
                        "是精妙無比，你忍不住想跟著學(think)起來了。\n" NOR;
        }

        return msg;
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if( query("special_skill/clever", me) )
                add = me->query_int() / 4;
        else
                add = me->query_int() / 10;

        if (! living(me) || arg != "bi")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙著呢。\n");

        if( me->query_skill("literate",1) || query("learned_literate", me) )
                return notify_fail("你發現石壁上的武功深奧之極，一時難以體會！\n");

        if( query("int", me)<27 )
                return notify_fail("你若有所悟，然而總是有點不明白。\n");

        if( query("dex", me)<27 )
                return notify_fail("你研究了半天，只覺招式始終無法隨意施展。\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("你的基本內功火候不夠，無法領悟石壁"
                                   "上的武功。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，無法學習石壁上的武功。\n");

        if( query("jing", me)<85 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        if ((int)me->query_skill("taixuan-gong", 1) < 60)
                return notify_fail("你覺得石壁上記載的武功對你來說過于復雜，一"
                                   "時難以領悟。\n");

        if ((int)me->query_skill("taixuan-gong", 1) >= 120)
                return notify_fail("你覺得石壁上記載的武功對你來說太淺了，結果你"
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