// Code of ShenZhou
// wsky, 5/7/00
inherit ROOM;

#include <ansi.h>

int do_hide();
int do_look();
int event_one(object me);
int event_two(object me);
int event_three(object me);

void create()
{
        set("short", "花叢中");
        set("long", @LONG
這裡是終南山後山的花叢中，這叢紅花排開來長達數丈，密密層
層，奇香撲鼻。但見花叢有如一面大屏風，紅瓣綠枝，煞是好看，四
下裡樹蔭垂蓋，便似天然結成的一座花房樹屋。這些紅花(flowers)似
乎可以推開。
LONG );

        set("item_desc", ([
                "flowers" : "這花叢既深且密，到是一個很好的藏身之處。\n",
        ]));

        set("no_clean_up", 0);

        set("outdoors", "quanzhen");

        set("cost", 2);
        setup();
        

}

void init()
{       
        add_action("do_hide", "hide");
        add_action("do_hide", "cang");
        add_action("do_push", "push");
        add_action("do_push", "tui");
}

int do_hide(){

        object me=this_player();
        if (me->is_busy())
                return notify_fail("你現在正忙著哪！\n");

        if( query_temp("hiding", me) )
                return notify_fail("你已經藏好了。\n");
        
        if( query_temp("found_lianhuan_book", me) )
                return notify_fail("你還藏什麼？\n");
        
        tell_object(me, "你小心翼翼地藏到了花叢中。\n");
        
        set_temp("hiding", 1, me);
        
        
        call_out("event_one", 10, me);
        
        return 1;
}

int do_push(){

        object room;
        object me=this_player();
        
        if (me->is_busy())
                return notify_fail("你現在正忙著哪！\n");

        tell_object(me, "你輕輕地推開花木，向外走了出去。\n");
        
        set_temp("hiding", 1, me);
        delete_temp("hiding", me);
        
        room = load_object("/d/quanzhen/milin");
        
        set("hide_person", 1, room);
        delete("hide_person", room);
        
        me->move(room);
        return 1;

}

int event_one(object me){
        
        if( query_temp("hiding", me)){
        
                tell_object(me, HIG"突然間山後傳來腳步聲響，兩個人一面說話，一面走近。原來竟是尹志平和趙志敬。兩個人越說越大聲，竟似在互相爭辯。\n"NOR);
                
                remove_call_out("event_one");
                call_out("event_two", 5, me);
        }

        return 1;
}

int event_two(object me){
        
        if( query_temp("hiding", me)){
        
                tell_object(me, HIG"只聽見趙志凈冷笑到：“你不守清規，犯了我教的大戒，怎能再做首座弟子？”你心下納悶，不知趙志敬什麼意思。\n"NOR);
                tell_object(me, HIG"你心中嘀咕中，尹趙兩人已越吵越兇。突然間，趙志敬喊道：“你還敢抵賴？咱們招丘師伯評理去！\n"NOR);
                tell_object(me, HIG"尹志平再也忍耐不住，唰地一聲，長劍出鞘，分心便刺，趙志敬側身避開，抽劍出匣，兩人打到一起。\n"NOR);
                
                remove_call_out("event_one");
                call_out("event_three", 15, me);
        }
        
        return 1;
}


int event_three(object me){
        
        if( query_temp("hiding", me)){
        
                tell_object(me, HIG"只見尹趙而人出招凌厲變幻，已非你所知，你不禁手心中全是冷汗。\n"NOR);
                tell_object(me, HIR"\n\n再拆數招，尹志平左劍平刺，右掌正擊，同時左腿橫掃而出，正是全真派中的“三連環”絕招。\n"NOR);
                                
                remove_call_out("event_two");
                call_out("event_four", 15, me);
        }
        
        return 1;
}

int event_four(object me){
        
        object book;
        
        if( query_temp("hiding", me)){
        
                tell_object(me, HIG"只見尹志平大聲怒喝，連走險招，竟然不再擋駕對方來招，一味猛攻。\n"NOR);
                tell_object(me, HIG"\n\n再拆數招，趙志敬在對方拼命下漸漸招架不住，撒腿向別處逃去。\n"NOR);
                
                tell_object(me, HIY"\n\n尹志平一愣，隨後追去，你只聽見嗒地一聲，一本小冊子從尹志平身上掉了下來。\n"NOR);
                tell_object(me, "\n\n待尹志平走後，你忙起身將那小冊子揀了起來。\n"NOR);
                
                set_temp("found_lianhuan_book", 1, me);
                delete_temp("hiding", me);
                book=new("/d/quanzhen/obj/lh_book");
                set("player_id",query("id",  me), book);
                book->move(me);
                                                
                remove_call_out("event_three");
                
        }
        
        return 1;
}
