#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "苗園");
        set("long", @LONG
這裏是苗鋪主人用來養花的花棚，一個大大的温室，將各種樣的奇花
異草呵護在其中，當然花叢中更多的是牡丹，只見那牡丹紅的，白的，黑
的，紫的，黃的，各色各樣，爭奇鬥豔，嬌豔欲滴，不愧和白馬寺一起成
為了洛陽的象徵。你也可以在這裏種花。
LONG);
        set("outdoors", "luoyang");
        set("no_fight",1);
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"miaopu",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2110);
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
        object ob, me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, "你種子都沒有，還想種花？\n"); 
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me, "你已經完成了培育這道程序，現在可以澆水"
                                HIY "(jiaoshui)" NOR "。\n");
                return 1;
        }

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "你的經驗尚淺，還是先到處多走動走動吧。\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "以你的身份大概不適合種花了吧。\n");
                return 1;
        }

        if( query("jing", me)<70 )
        {
                tell_object(me, "你已經很疲憊了，休息一下再接着種吧。\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "把土坑周圍好好地修整了一下，使土壤更加"
                       "適合花的生長。\n" NOR, me); 
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me, ob;
        int exp, pot;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me, "你已經很疲憊了，休息一下再接着種吧。\n");
                return 1;
        }
        if (me->is_busy())
        {
                tell_object(me, "你正忙着呢，彆着急。\n");
                return 1;
        }
        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me, "你沒事幹澆什麼水啊！\n");
                return 1;
        }
        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) < 4)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/clone/megazine/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 8)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        message_vision(HIY "$N" HIY "種出了一朵翡翠蘭。\n"
                                                       NOR, me);
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
                                message_vision(HIY "$N" HIY "種出了一朵無名花。\n" NOR,me);
                                return 1;
                        }
                        message_vision(HIC "$N" HIC "十分小心的給小坑裏澆了一些"
                                       "水，突然一朵"+query("name", ob)+HIC
                                       "從坑裏冒了出來。\n" NOR, me);   
                        message_vision(HIY "$N" HIY "把它摘了下來，拿在手裏。\n" NOR, me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);

                        exp = 10 + random(10);
                        pot = 2 + random(3);

                        if( query("potential", me)>me->query_potential_limit() )
                                pot = 1;

                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);

                        tell_object(me, HIC "通過這次訓練，你獲得了" + chinese_number(exp)
                                        + "點經驗和" + chinese_number(pot) + "點潛能。\n"
                                        NOR);
                        return 1; 
                }
                message_vision(HIR "$N" HIR "笨手笨腳的拿起水壺給小坑裏澆水，結"
                               "果水灑的太多把花給毀了。\n", me); 
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
                message_vision(HIC "$N" HIC "拿起水壺給小坑澆了一些水。\n" NOR, me); 
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2)); 
                return 1;
        }
}