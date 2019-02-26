// /d/xiakedao/shishi24.c 俠客島 石室24

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "石室");
        set("long", @LONG
這裏火光昏暗，只見那龍島主與木島主盤膝坐在錦墊之上，面對
石壁(wall)，凝神苦思。此石室已是山腹最深處，卻寬闊高大，足可
容下近百人。洞中火把亦是其他洞的二三倍之多。
LONG );
        set("exits", ([
                "east" : __DIR__"shihole6",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「白首太玄經」幾個大字。字的下方刻的是密密麻麻
的蝌蚪文，成千上萬。文字排列甚不整齊，或橫或豎，或直或斜。左
下的大片甚至混成一團難分次序，委實難以辨認。
WALL
        ]));
        set("objects", ([
                CLASS_D("xiakedao") + "/long" : 1,
                CLASS_D("xiakedao") + "/mu"   : 1,
        ]));
        set("no_fight", 1);
        set("coor/x", -3100);
        set("coor/y", -25600);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_study", "think");
        add_action("do_study", "study");
        add_action("do_canwu", "canwu");
}

int do_canwu(string msg)
{
        object me = this_player();
        string where, witch;

        if (! msg) return notify_fail("什麼？\n");

        if (sscanf(msg, "%s from %s", witch, where) != 2)
                return notify_fail("幹什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("你在戰鬥哦？！小心，來了！！！\n");

        if (witch != "白首太玄經")
                return notify_fail("你想參悟什麼？\n");

        if (where != "wall")
                return notify_fail("這裏沒什麼給你參悟的啊！\n");

        if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
                return notify_fail("你對着石壁想了半天也沒發現什麼！\n");

        if ((int)me->query_skill("force", 1) < 340)
                return notify_fail("你的內功修為不夠，無法貫通石壁上的絕學！\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你的內力修為不足，無法貫通石壁上的絕學！\n");

        if( query("jing", me)<100 )
                return notify_fail("你的精力無法集中，無法領悟石壁上的絕學！\n");

        if (me->query_skill("taixuan-gong", 1) < 340)
                return notify_fail("你對太玄功所知實在有限，無法領悟石壁上的絕學！\n");

        if( query("can_perform/taixuan-gong/jing", me) )
                return notify_fail("這項絕學你不是已經會了嗎？\n");

        me->receive_damage("jing", 95);

        me->start_busy(2 + random(4));

        if (random(50) == 1 || wizardp(me))
        {
                addn("taixuan_perform/jing/count", 1, me);

                if( query("taixuan_perform/jing/count", me) >= 300 )
                {
                        write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
                        write(HIC "你終於通曉了絕學「白首太玄經」。\n" NOR);

                        set("can_perform/taixuan-gong/jing", 1, me);
                        delete("taixuan_perform/jing/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "你對「白首太玄經」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else return notify_fail("你試圖從石壁上研究有關「" + witch + "」的內容，但卻沒什麼效果！\n");

}

int do_study(string arg)
{
        object me;
        int lvl;

        if (arg != "wall")
                return notify_fail("你想研究什麼？\n");

        me = this_player();
        if( query("combat_exp", me)<500000 )
        {
                write("你看了半天，只恨自己實戰經驗太淺薄，無法領悟上面的高深知識。\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙，沒空研究上面的詩句。\n");
                return 1;
        }

        me->receive_damage("jing", 15);
        me->start_busy(1);

        lvl = me->query_skill("literate", 1);
        if (lvl >= 200)
                write("你看了半天，覺得這首詩寫的很好，不過似乎沒什麼特別之處。\n");
        else
        if (lvl >= 100)
                write("你覺得這上面的詩大有寓意，不由的盡心苦思。\n");
        else
        if (lvl >= 1)
                write("你心中暗想：這定是前輩高手留下的祕籍，這些詞句可要好好分析。\n");
        else
        if (random(2))
        {
                write("你望着上面的筆劃，想起所修習的武功來，不禁漸漸有所體會。\n");
                if( query("experience", me)<me->query_experience_limit() )
                        addn("experience", 1, me);
        } else
                write("你潛心琢磨上面的筆劃，全然沒有想它是什麼含義。\n");

        return 1;
}
