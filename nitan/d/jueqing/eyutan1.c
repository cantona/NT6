#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "鄂魚潭岸上");
        set("long", @LONG
鄂魚潭深處地底，寒似冰窟。潭中(tan)一團黑子晃動，仔
細一看竟是許多兇猛的鄂魚。 只見不遠處似有一個洞口，但由
於深潭相隔，不知如何過去。

LONG);
        set("item_desc",([
               "tan" : HIC "潭中鄂魚成羣，兇猛無比。 恐怕只有"
                       "施展輕功穿(cross)過去了。\n" NOR,
        ]));

        set("no_clean_up", 0);

        setup();

}

void init()
{       
        add_action("do_cross", ({ "cross" }));
}

int do_cross(string arg)
{
        object me = this_player();
        object ob1, ob2, ob3;
        int n;
        string msg;

        if (! arg || arg != "tan" )
                return notify_fail("你要往哪兒跳？\n");

        // ob1 鄂魚潭岸上
        if (! ob1 = find_object(__DIR__"eyutan1"))
                ob1 = load_object(__DIR__"eyutan1");

        // 若輕功不濟則掉如潭水中,   ob2 深潭
        if (! ob2 = find_object(__DIR__"eyutan2"))
                ob2 = load_object(__DIR__"eyutan2");

        // ob3 鄂魚潭對岸
        if (! ob3 = find_object(__DIR__"eyutan3"))
                ob3 = load_object(__DIR__"eyutan3");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");

        n = me->query_skill("dodge");
        
        if (n > 120)
        {   
            msg = HIY + me->name() + HIY "飛身前躍，跳向鄂魚潭，只見" + me->name() +
                  HIY "到至深潭上空卻又忽地落下，眼見要墜入潭中。卻見" + me->name() +
                  HIY "雙足在鄂魚背上一點，頃刻間騰向對岸。\n" NOR;
                      
            tell_room(ob1, sort_msg(msg), me);

            tell_object(me,  HIC "你飛身前躍，跳至深潭半空身雙足在鄂魚背上一點，眨"
                             "眼間已\n到得對岸。\n\n" NOR);

            tell_room(ob3, HIG + me->name() + HIG "從對岸跳了過來。\n" NOR, me);
        
            me->move(ob3);
        }     
        else
        {
            msg = HIR + me->name() + HIR "飛身前躍，跳向鄂魚潭，只見" + me->name() +
                  HIR "到至深潭上空卻力氣已盡，落入潭中。\n" NOR;

            tell_room(ob1, sort_msg(msg), me);

            tell_object(me,  HIR "你飛身前躍，跳至深潭半空身卻感覺力氣已盡，想回頭"
                            "已不能，\n只聽“撲咚”一聲，你已經落入深潭之中。\n\n" NOR);
             
            me->move(ob2);
        } 

        return 1;
}

