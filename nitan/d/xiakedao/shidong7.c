// Room: /xiakedao/shidong7.c

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
                "west" : __DIR__"shidong8",
                "north" : __DIR__"shidong6",
        ]));
        set("no_clean_up", 0);
        set("item_desc",([
                "bi"  : (: look_bi :),
                "weapon": "圖中人物手持刀劍，互相揮砍……\n",
        ]));
        set("coor/x", -3100);
        set("coor/y", -22100);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_think", "think");
        add_action("do_canwu", "canwu");
}

string look_bi()
{
        object me = this_player();
        string msg;

        if( me->query_skill("literate", 1)
         || query("learned_literate", me)){
                msg = HIC "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁佈滿\n"
                        "蝌蚪形狀的文字。你仔細推敲這些文字卻一無所獲。\n" NOR;
        } else {
                msg = HIC "\n你走到石壁前，仔細觀看石壁上的內容，發現石壁佈滿\n"
                        "蝌蚪形狀的文字，由於你從未讀過書，所以你並沒有在\n"
                        "意那些文字。你猛然看到文字下面有很多圖畫，是用利\n"
                        "器所刻。上面畫着各式各樣的人物，有的手持長劍，有\n"
                        "的手握鋼刀……但見圖中人物手中兵器(weapon)不盡相\n"
                        "同，每個人物的武功招式也不同，但是上面人物卻仍舊\n"
                        "裸露全身，其周身經脈走向清晰無比，配合着各種招式，\n"
                        "你似乎隱隱覺得其中隱藏着太玄功更高深絕招，似乎是\n"
                        "跟武器運用有密切關係， 但你一時卻也參悟(canwu)不\n"
                        "透，儘管如此，你卻忍不住想跟着學(think)起來。\n" NOR;
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

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("你的基本內功火候不夠，無法領悟石壁"
                                   "上的武功。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，無法學習石壁上的武功。\n");

        if( query("jing", me)<85 )
                return notify_fail("你現在精神不濟，過於疲倦，還是休息"
                                   "一會吧。\n");

        if ((int)me->query_skill("taixuan-gong", 1) < 120)
                return notify_fail("你覺得石壁上記載的武功對你來説過於複雜，一"
                                   "時難以領悟。\n");

        if ((int)me->query_skill("taixuan-gong", 1) >= 180)
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

int do_canwu(string msg)
{
    object me = this_player();

    string where, witch;

    if (! msg)return notify_fail("什麼？\n");

    if (sscanf(msg, "%s from %s", witch, where) != 2)
          return notify_fail("幹什麼？\n");

    if (me->is_busy())
          return notify_fail("你現在正忙着呢。\n");

    if (me->is_fighting())
          return notify_fail("你在戰鬥哦？！小心，來了！！！\n");

    if (witch != "weapon")
          return notify_fail("你想參悟什麼？\n");

    if (where != "bi")
          return notify_fail("這裏沒什麼給你參悟的啊！\n");

    if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
          return notify_fail("你對着石壁想了半天也沒發現什麼！\n");

    if ((int)me->query_skill("force", 1) < 240)
          return notify_fail("你的內功修為不夠，無法領悟如何利用"
                             "太玄功來駕御兵器！\n");

    if( query("max_neili", me)<6000 )
          return notify_fail("你的內力修為不足，無法領悟如何利用"
                             "太玄功來駕御兵器！\n");

    if( query("jing", me)<100 )
          return notify_fail("你的精力無法集中，無法領悟如何利用"
                             "太玄功來駕御兵器！\n");

    if (me->query_skill("taixuan-gong", 1) < 200)
          return notify_fail("你對太玄功所知實在有限，無法領悟如何利用"
                             "太玄功來駕御兵器！\n");

    if( query("can_learned/taixuan-gong/enable_weapon", me) )
          return notify_fail("石壁上的絕技你早已融會貫通，不必再參悟了。\n");

    me->receive_damage("jing", 95);

    me->start_busy(3 + random(5));

    if (random(6) == 1)
    {
        addn("canwu_taixuan/count", 1, me);

        if( query("canwu_taixuan/count", me) >= 50 )
        {
            write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
            write(HIC "你終於通曉瞭如何利用太玄功來駕御兵器。\n" NOR);

            set("can_learned/taixuan-gong/enable_weapon", 1, me);
            delete("canwu_taixuan/count", me);

            if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
            if (me->can_improve_skill("taixuan-gong"))
                    me->improve_skill("taixuan-gong", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你對如何利用太玄功來駕御兵器有了更新的認識，但其中仍然有許"
                  "多不解之處。\n" NOR);
        return 1;
    }
    else return notify_fail("你仔細研究石壁上所刻畫的內容，但卻沒什麼效果！\n");

}