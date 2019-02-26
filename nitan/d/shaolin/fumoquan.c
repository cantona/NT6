#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "金剛伏魔圈");
        set("long", @LONG
三棵大松樹的樹幹上各挖了個可容身一人的大洞，有個洞口露出
黑色僧袍一角，似乎住得有人。中央是一片大草坪，中心處光禿禿的，
似乎經常受大力擊打，以致寸草不生。
LONG );
        set("exits", ([
                "out" : __DIR__"qyping",
        ]));

        set("objects",([
                CLASS_D("shaolin") + "/du-nan" : 1,
                CLASS_D("shaolin") + "/du-e" : 1,
                CLASS_D("shaolin") + "/du-jie" : 1,
        ]));
        setup();
}

void init()
{
        mapping mine;
        object me;
        object ob1, ob2, ob3;

        me = this_player();
        mine=query("family", this_player());

        if( query_temp("valid_in_fumoquan", me) )
                return;

        if (mapp(mine) &&
            mine["family_name"] == "少林派" &&
            mine["generation"] <= 36)
        {
                set_temp("valid_in_fumoquan", 1, me);
                return;
        }

        if (! objectp(ob1 = present("du nan", this_object()))
           || ! living(ob1)
           || ! objectp(ob2 = present("du e", this_object()))
           || ! living(ob2)
           || ! objectp(ob3 = present("du jie", this_object()))
           || ! living(ob3)
           || ! interactive(me))
        {
                set_temp("valid_in_fumoquan", 2, me);
                return;
        }

        if (ultrap(me))
        {
                message_sort(WHT "\n但見三位老僧紋絲不動，鎮定不若，恍"
                             "若不知道$N的到來。\n\n" NOR, me);
                CHANNEL_D->do_channel(this_object(), "rumor", "大宗師" +
                                      me->name(1) + "進入金剛伏魔圈。");
                set_temp("valid_in_fumoquan", 1, me);
                return;
        }

        message_sort(HIR "\n突然間勁氣縱橫，三根黑索如三條黑蟒般就地滾"
                     "來，瞬間近身，化成一條筆自的兵刃，如長矛，如杆棒"
                     "，如利劍，分別向$N的頭，胸，腹三處要害疾刺而至。"
                     "$N一瞥間，看到三個老僧分居三個樹洞之中，正全力持"
                     "鞭向$N攻來！$N已陷身於少林寺之藴含無上降魔大法的"
                     "金剛伏魔圈！\n" NOR, me);

        if (mapp(mine) &&
            mine["family_name"] == "少林派" &&
            query("combat_exp",this_player()) < 100000 )
        {
                message_vision(HIR "\n突然$N" HIR "被一道排山倒海般的勁"
                               "氣擊中，頓時飛了出去。\n\n" NOR, me);
                me->move("/d/shaolin/qyping");
        }

        message_vision(WHT "\n忽然間「颼」的一聲，一股罡風從$N"
                       WHT "左首處悄然湧至。\n" NOR, me);

        COMBAT_D->do_attack(ob1, me, query_temp("weapon"));

        message_vision(WHT "\n緊跟着破空聲大起，又是一股罡風從$N"
                       WHT "的右首處襲來。\n" NOR, me);

        COMBAT_D->do_attack(ob2, me, query_temp("weapon"));

        message_vision(WHT "\n最後只聽一聲「" HIW "我佛慈悲" NOR +
                       WHT "」。數股罡風已籠罩$N" WHT "周身！\n" NOR, me);

        COMBAT_D->do_attack(ob3, me, query_temp("weapon"));

        if( query("qi", me)<0 )
        {

                if (mapp(mine) && mine["family_name"] == "少林派")
                {
                        me->unconcious();
                        set_temp("valid_in_fumoquan", 2, me);
                } else
                {
                        set_temp("die_reason", "強闖金剛伏魔圈，徒然送了性命", me);
                        me->die();
                }
                return;
        }

        set_temp("valid_in_fumoquan", 1, me);
        message_vision(WHT "\n此時三位老僧收回鞭子，哼了一聲。\n\n" NOR, me);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              (mapp(mine) ? mine["family_name"] : "") +
                              me->name(1) + "闖入金剛伏魔圈。");
}

int valid_leave(object me, string dir)
{
        delete_temp("valid_in_fumoquan", me);
        return ::valid_leave(me, dir);
}
