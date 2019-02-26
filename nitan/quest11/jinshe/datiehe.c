// Room: /d/huashan/jinshe/obj/datiehe.c
// Date: Look 99/03/25

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("大鐵盒" , ({ "tie he", "box" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個兩尺來高的鐵盒子，上面滿是了泥土。\n");
                set("value", 1000);
                set("material", "steel");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
                }
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_open", "open");
        add_action("do_move", "move");
}

int do_open(string arg)
{
        object me = this_player();
        object ob;

    if( query_temp("open", me) && geteuid(me) != "yueying" )
          return notify_fail("你已經打開盒子了\n");   
    if (!arg || (arg != "box" && arg != "tie he"))
       {
        return notify_fail("你想打開什麼？\n");
        return 1;
       }
    else
    {  
    if( !present("jiaxin",me) && query("quest/jinshe2/xin", me) )
    {
          ob=unew(__DIR__"jiaxin");
          if (random(20)> 20) {
                        write("你打開鐵盒，發現裏面空空的什麼也沒有。\n");
                        write(HIG"看來有人已經取走了裏面的東西,你還是改天再來吧.\n"NOR);
        set_temp("open", 1, me);
                  return 1;
                 }
        ob->move(me);
        write(HIC"你輕開鐵匣，發現裏面平平整整放着一封書信,你連忙揀了起來。\n"NOR);
        
        set_temp("open", 1, me);
        return 1;       
      }
    if (!present("xin jian",me))
       {
        write("你輕開鐵匣，突然掉落了一張信箋，你急忙把它撿起。\n");
        ob=new(__DIR__"xinjian1");
        set_temp("mark/open", 1, me);
        set_temp("open", 1, me);
        ob->move(me);
        return 1;
       }
        write("你打開鐵盒，發現裏面空空的什麼也沒有。\n");
        return 1;
    }
}
int do_move(string arg)
{
        object me = this_player();
        object ob;
        if ( !arg || arg != "anceng" )
        return notify_fail("你要幹什麼？\n");
        if( !query_temp("mark/open", me) && !query_temp("mark/xin", me) )
         return notify_fail("你要做什麼？\n");
        
                write("你小心翼翼打開暗層.......\n");
                if( random(10)>8 || query("env/debug", me)){
                                          ob=unew(__DIR__"jinshezhui");
                                          if ( ob ){
                                                         ob->move(me);
                                                         delete_temp("mark/open", me);
                                                         delete_temp("mark/xin", me);
                                                         write(HIY"赫然發現,一柄金光閃閃的蛇型錐放在裏面,看起來很值錢的樣子,你開心極了,連忙把它揣進懷裏\n"NOR);
       set_temp("quest/金蛇劍法/金蛇錐", 1, this_player());
       set_temp("quest/金蛇掌法/start", 1, this_player());//開始標記bydaidai
                                                     return 1;
                                                    }
                                          else return 1;
                                          }          
                          
        message_vision(RED"$N突然看見幾道寒光撲面，大叫一聲，一陣抽搐。\n"NOR, me);
        delete_temp("mark/open", me);
        me->unconcious();
        return 1;
}
