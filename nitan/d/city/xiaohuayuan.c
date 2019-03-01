// xiaohuayuan.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIG "小花園" NOR);
        set("long", @LONG
這裡一個小花園，這裡的肥沃土壤十分適合各種花的生長，特別
地一些十分名貴的花種，這裡也可生長。你可以在這裡種花(zhonghua)。
花店裡可以買到花的種子。
LONG
        );

        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "south"  : __DIR__"huadian",
        ]));

        set("no_fight", 1);
	set("coor/x", 30);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_jiaoshui", "jiaoshui");
        add_action("do_peiyu", "peiyu");
}

int do_peiyu()
{
        object ob,me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, HIR "你種子都沒有，還想種花？\n" NOR);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me,HIR "你已經完成了培育這道程序，現在可以澆水(jiaoshui)。\n" NOR);
                return 1;
        }

        if( query("combat_exp", me)>150000 || query("combat_exp", me)<10000 )
        {
                tell_object(me,HIR "以你的身份大概不適合在小花園種花吧！\n" NOR);
                return 1;
        }

        if( query("jing", me)<70 )
        {
                message_vision(HIR "$N一幅氣喘吁吁的樣子，怎麼能種花呢！\n" NOR,me);
                return 1;
        }

        message_vision("$N把土坑周圍好好地修整了一下，使土壤更加適合花的生長。\n", me);
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me,ob;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me,HIR "你氣色不好，還是休息休息吧。\n" NOR);
                return 1;
        }

        if (me->is_busy())
        {
                tell_object(me, HIR "你正忙著呢，別著急。\n" NOR);
                return 1;
        }

        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me,HIR "你是來搗亂嗎？沒事幹澆什麼水啊！\n" NOR);
                return 1;
        }

        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) == 1)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/d/changan/npc/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 1)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        CHANNEL_D->do_channel(this_object(), "rumor",
                                                              query("name", me)+"從小花園種出一朵翡翠蘭。");
                                        message_vision(HIR "$N" HIR "得到了翡翠蘭。\n" NOR,me);
                                        ob->move(me, 1);
                                        delete_temp("jiaoshui", me);
                                        delete_temp("zhonghua", me);
                                        delete_temp("peiyu", me);
                                        addn("combat_exp", 500, me);
                                        me->improve_potential(100 + random(100));
                                        return 1;
                                }

                                ob = new("/d/shenlong/obj/hua2");
                                addn("combat_exp", 20+random(10), me);
                                me->improve_potential(20 + random(10));
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                      query("name", me)+"從小花園種出一朵無名花。");
                                return 1;
                        }

                        message_vision(HIC "$N" HIC "十分小心的給小坑裡澆了一些水，突然" +
                                       query("long", ob)+"從坑裡冒了出來。\n"NOR,me);
                        message_vision(HIR "$N" HIR "把它摘了下來，拿在手裡。\n" NOR,me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);
                        addn("combat_exp", 20+random(10), me);
                        me->improve_potential(10 + random(10));
                        return 1;
                }

                message_vision(HIR "$N" HIR "笨手笨腳的拿起水壺給小坑裡澆水，結果水"
                               "洒的太多把花給毀了。\n",me);
                delete_temp("jiaoshui", me);
                delete_temp("zhonghua", me);
                delete_temp("peiyu", me);
                addn("jing", -50, me);
                addn("combat_exp", 3, me);
                me->improve_potential(2);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                message_vision("$N拿起水壺給小坑澆了一些水。\n",me);
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2));
                return 1;
        }
}