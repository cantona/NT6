// /clone/misc/chutou.c
// Last modified by winder 2003.9.2

inherit ITEM;
#include <ansi.h>;
int do_wajue();

void create()
{
        set_name(HIG"鋤頭"NOR, ({ "chu tou", "bao chu", "chu" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把發着黑亮熒光的特製精鋼鋤頭，你好像可以用它挖掘(wajue)什麼東西。\n");
                set("wajue", 0);
//                set("no_sell",1);
//                set("no_drop",1);
/*                set("no_put",1);
                set("no_get",1);
                set("no_beg",1);
                set("no_steal",1);        
*/                set("value", 1000000);
                set("no_value",1); // drop時丟失
                set("material", "steel");
                 
        }
        
        setup();
}

void init()
{
        add_action("do_wajue", "wajue");
}

int do_wajue()
{
        int t, time;
        string *dir, target;
        object ob, me = this_player(), where = environment(me),obj;
//        return 1;
        t=time()-query_temp("wajue", where);
        time=query_temp("wajue1", where);

        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");
        if (!present("bao chu", me))
                return notify_fail("你沒有鋤頭，怎麼挖掘呀？！\n");
        
                
        if (!wizardp(me))
        {
                obj = present("chu tou", me);
                if( query("jing", me)<50 )
                        return notify_fail("你挖了半天，精力不夠了！\n");
                if( !query("outdoors", environment(me)) )
                        return notify_fail("在房子裏你也想挖寶？！\n");
                if (present("bao wu",me))
                        return notify_fail("你身上已經有寶物了，別太貪心！\n");
                if( query_temp("baowunum", me) >= 1 )
                        return notify_fail("韋爵爺正派人四處尋你呢，還不快去？\n");
                if( t <= time && !(query_temp("invite", me) && random(2) == 1) )
                        return notify_fail("這裏已被人挖過，一會兒再來吧！\n");
                if (me->is_fighting()) 
                        return notify_fail("現在正打得起勁，哪有空挖呢？！\n");
        }
        if (random(10) <= 6 )
        {
                printf(HIC"你拿出一把鋤頭，在地上挖了半天，什麼也沒有挖到。\n"NOR);
                t = (300 + random(10) );
                set_temp("wajue", time(), where);
                set_temp("wajue1", t, where);
    if (random(30) <= 2)
    if( query_temp("invite", me))me->start_busy(2);
    else  me->start_busy(1);
                return 1;
        }
        else
        { 
                printf( HIC"你拿出一把鋤頭，在地上挖了半天，突然你覺得好像挖到了什麼。\n"NOR);   
                switch (random(10))
                {
                        case 0:
                        case 1:
                        case 2:
                                ob = new(__DIR__"baowu");
                                set("owner",query("id",  me), ob);
                                ob->move(me);
                                tell_object(me, HIW"由於你辛勤的挖掘，你發現了一個寶物。\n"NOR);
                                tell_object(me, HIW"恭喜你啦！\n"NOR);                                
                                addn_temp("baowunum", 1, me);
                                break;
                        case 3:
                                dir = get_dir("/clone/food/fruit/");
                                ob = new("/clone/food/fruit/"+dir[random(sizeof(dir))]);
//                                ob->set("owner",me->query("id"));
                                ob->move(me);
                                tell_object(me, HIW"由於你辛勤的挖掘，你發現了一些東東。\n"NOR);
                                break;
                        case 4:
                        case 5:
                                dir = get_dir("/clone/medicine/vegetable/");
                                ob = new("/clone/medicine/vegetable/"+dir[random(sizeof(dir))]);
                                if( query("id", ob) == "lingzhi" || query("id", ob) == "fuxincao" || query("id", ob) == "xuelian" )
                                {
                                message_vision("哇，$N挖到了一個茅坑。\n", me);
                                tell_object(me,"這麼快就連茅坑都能挖出來，佩服啊佩服。\n");
                                break;
                                }
//                                ob->set("owner",me->query("id"));
                                ob->move(me);
                                tell_object(me, HIW"由於你辛勤的挖掘，你發現了一些藥材。\n"NOR);
                                break;
                        case 6:
/*
                                message_vision("哎呀不好，$N挖到蛇窩了！一條毒蛇從洞裏鑽了出來。\n", me);
                                tell_object(me,"還不快跑？\n");
                                ob = new("/clone/animal/snake");
                                ob->move(environment(me));
                                break;
*/
                        case 7:
/*
                                message_vision("一鋤頭下去，$N挖出一窩兔子。\n", me);
                                ob = new("/clone/animal/yetu");
                                ob->move(environment(me));
                                break;
*/
                        case 8:
                                message_vision("哇，$N挖到了一個茅坑。\n", me);
                                tell_object(me,"這麼快就連茅坑都能挖出來，佩服啊佩服。\n");
                                break;
                        default:
                                message_vision("哇，$N挖出了一口井。\n", me);
                                tell_object(me,"可惜挖的地方不對，這井除了冒煙，什麼也不會。\n");
                }
                
                t = ( 30 + random(10) ) * 100;
                set_temp("wajue", time(), where);
                set_temp("wajue1", t, where);
                me->receive_damage("jing", 20);
                return 1;
        }
}
