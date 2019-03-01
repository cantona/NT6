// shidong10.c 石洞

inherit ROOM;

#include <ansi.h>

string look_bi();

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石室，隱約可以感覺到四周是堅硬的石壁(bi)，
石洞內幹幹凈凈，一塵不染。
LONG );
        set("exits", ([
                "east" : __DIR__"shidong9",
                "out"  : __DIR__"dating",
        ]));

        set("objects", ([
                //__DIR__"obj/baihongjian" : 1,
                WEAPON_DIR"treasure/baihong-jian" : 1,
        ]));

        set("item_desc",([
                "bi"  : (: look_bi :),
        ]));
        set("coor/x", -3110);
        set("coor/y", -22070);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
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
                msg = HIW "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁布滿\n"
                        "蝌蚪形狀的文字，由于你從未讀過書，所以你並沒有在\n"
                        "意那些文字。你猛然看到文字下面有很多圖畫，是用利\n"
                        "器所刻。但見畫中人物神情怪異，手舞足蹈，似乎是什\n"
                        "麼厲害的神功絕技。你禁不住想……\n" NOR;
        }

        return msg;
}

int do_canwu(string msg)
{
        object me = this_player();

        string where, witch;

        if (! msg) return notify_fail("什麼？\n");

        if (sscanf(msg, "%s from %s", witch, where) != 2)
                return notify_fail("幹什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("你在戰鬥哦？！小心，來了！！！\n");

        if (witch != "太玄激勁"
        &&  witch != "乘風破浪"
        &&  witch != "混天一氣")
                return notify_fail("你想參悟什麼？\n");

        if (where != "bi")
                return notify_fail("這裡沒什麼給你參悟的啊！\n");

        if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
                return notify_fail("你對著石壁想了半天也沒發現什麼！\n");

        if ((int)me->query_skill("force", 1) < 240)
                return notify_fail("你的內功修為不夠，無法貫通石壁上的絕學！\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你的內力修為不足，無法貫通石壁上的絕學！\n");

        if( query("jing", me)<100 )
                return notify_fail("你的精力無法集中，無法領悟石壁上的絕學！\n");

        if (me->query_skill("taixuan-gong", 1) < 200)
                return notify_fail("你對太玄功所知實在有限，無法領悟石壁上的絕學！\n");

        if (witch == "混天一氣"
         && query("can_perform/taixuan-gong/hun", me) )
                return notify_fail("這項絕學你不是已經會了嗎？\n");

        else
        if (witch == "太玄激勁"
         && query("can_perform/taixuan-gong/xuan", me) )
                return notify_fail("這項絕學你不是已經會了嗎？\n");

        else
        if (witch == "乘風破浪"
         && query("can_perform/taixuan-gong/po", me) )
                return notify_fail("這項絕學你不是已經會了嗎？\n");

        me->receive_damage("jing", 95);

        me->start_busy(2 + random(4));

        if (random(13) == 1 && witch == "太玄激勁")
        {
                addn("taixuan_perform/xuan/count", 1, me);

                if( query("taixuan_perform/xuan/count", me) >= 60 )
                {
                        write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
                        write(HIC "你終于通曉了絕學「太玄激勁」。\n" NOR);

                        set("can_perform/taixuan-gong/xuan", 1, me);
                        delete("taixuan_perform/xuan/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "你對「太玄激勁」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else
        if (random(4) == 1 && witch == "混天一氣")
        {
                addn("taixuan_perform/hun/count", 1, me);

                if( query("taixuan_perform/hun/count", me) >= 30 )
                {
                        write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
                        write(HIC "你終于通曉了絕學「混天一氣」。\n" NOR);

                        set("can_perform/taixuan-gong/hun", 1, me);
                        delete("taixuan_perform/hun/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "你對「混天一氣」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else
        if (random(12) == 1 && witch == "乘風破浪")
        {
                addn("taixuan_perform/po/count", 1, me);

                if( query("taixuan_perform/po/count", me) >= 70 )
                {
                        write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
                        write(HIC "你終于通曉了絕學「乘風破浪」。\n" NOR);

                        set("can_perform/taixuan-gong/po", 1, me);
                        delete("taixuan_perform/po/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "你對「乘風破浪」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else return notify_fail("你試圖從石壁上研究有關「" + witch + "」的內容，但卻沒什麼效果！\n");

}

int valid_leave(object me,string dir)
{
        if (dir == "out")
                tell_object(me,"你走出了石洞，神秘地出現在大廳之中。\n");

        return ::valid_leave(me,dir);
}