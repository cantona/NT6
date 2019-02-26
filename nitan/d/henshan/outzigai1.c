#include <ansi.h>
inherit ROOM;

string look_bi(object me,string msg);
void auto_close();

void create()
{
        set("short","突石上");
        set("long", @LONG
站在這裏向下望才發現自己已經離地面有十來丈高了，尋望洞內
發現四周雖都有突石，但是唯有腳下這塊能容人站在上面觀望。仔細
觀察突石周圍發現身後的石壁(bi)中竟有一絲細小的裂縫，方才在下
面看到的光亮就是從這裂縫中投射出來的。
LONG );
        set("exits",([
               "down":__DIR__"outzigai",                
        ]));

        set("no_fight",1);

        set("item_desc",([
               "bi":(:look_bi:),
        ]));
        
        setup();

}


string look_bi(object me,string msg)
{
        object here;

        me = this_player();

        if ( !here = find_object(__DIR__"outzigai1"))
              here = load_object(__DIR__"outzigai1");
        

        if( query_temp("marks/破", here) )
                return "石壁已經被打破了。\n";
        
        if( query_temp("marks/推", here) )
                return HIC"\n石門已經被推開了，卻露出一個山洞來。\n"NOR;

        msg="這塊石壁看起來很堅實，也許是由於長年被水流沖蝕，上面已\n經出現了"
            "一條細小的裂縫。一絲陽光從縫中投射進來，看來外\n面應該有出路了。\n";

        return msg;
                          
}


void init()
{
        object me = this_player();
        object here;
        string msg;

        if ( !here = find_object(__DIR__"outzigai1"))
              here = load_object(__DIR__"outzigai1");
         
        if( query_temp("marks/推", here) )
        {
       tell_object(me,HIY"陽光照射在你臉上，你感到舒服極了。\n"NOR);

       delete("long");
       set("long",HIY @LONG
你環視四周，發現這裏距地面竟有十來丈高了，陽光從身
後的洞中灑了出來，石壁上水珠反射出耀眼的光環，突石上的
青苔也顯"得綠油油的，你覺得渾身説不出的暢快。
LONG);
        }
          
        add_action("do_tiao",({"tiao","jump"}));
        add_action("do_push",({"tui","push"}));
}

int do_tiao(string arg)
{        
        object me = this_player(),ob;

        if ( !ob = find_object(__DIR__"outzigai"))
              ob = load_object(__DIR__"outzigai");
        
        if( !arg || arg != "down")
                return notify_fail("你要往哪兒跳？\n");

        if (me->query_skill("dodge",1) < 120)
        {
        message_vision("\n$N鼓起勇氣縱身往下一跳...\n",me);
        me->unconcious();        
        me->move(__DIR__"outzigai");
        tell_room(ob,""+me->name()+"從上面摔了下來，昏倒了。\n");
        return 1;
        }
        
        message_vision("\n$N你縱身一跳，穩穩地落在了地上。\n\n",me);
        me->move(__DIR__"outzigai");
        message("vision",""+me->name()+"從上面跳了下來。\n",ob,me);
        return 1;
        
}

int do_push(string arg)
{
        object me = this_player(),obj,obhere;
        string msg;

        if ( !obj = find_object(__DIR__"zigaihole"))
              obj = load_object(__DIR__"zigaihole");

        if ( !obhere = find_object(__DIR__"outzigai1"))
              obhere = load_object(__DIR__"outzigai1");        

        if ( !arg || arg != "bi")
        {
        write("你要推什麼？\n");
        return 1;
        }

        if( query_temp("marks/推", obhere) )
        {
        write("石門已經被推開了。\n");
        return 1;
        }
        
        if( query("neili", me)<1500 || me->query_skill("unarmed",1)<80 )
        {                
        write("你使出渾身解數用力推石壁，可以石壁卻紋絲不動。\n");
        return 1;
        }

        msg = HIC"\n$N用力將石壁往旁邊一推，轟！地一聲，石壁已被推開，露出"NOR;
        msg += HIC"一個山洞來。這竟是一扇石門。\n\n"NOR;

        message_vision(msg,me);

        tell_room(obhere,HIY"陽光照射了進來，耀眼奪目。\n\n"NOR);
        tell_room(obj,HIC"洞外轟！地一聲，像是有人將石門推開了。\n"NOR);

        set("exits/enter",__DIR__"zigaihole");

        set_temp("marks/推", 1, obhere);
        set_temp("marks/推", 1, obj);
        set("exits/out", __DIR__"outzigai1", obj);

        if( query_temp("marks/推", obhere) )
        {

         delete("long");
       set("long",HIY @LONG
你環視四周，發現這裏距地面竟有十來丈高了，陽光從身
後的洞中灑了出來，石壁上水珠反射出耀眼的光環，突石上的
青苔也顯"得綠油油的，你覺得渾身説不出的暢快。
LONG);
        }

        call_out("auto_close",13);

        return 1;
}

void auto_close()
{
        object obin,obout,me=this_player();

        if ( !obin = find_object(__DIR__"zigaihole"))
              obin = load_object(__DIR__"zigaihole");

        if ( !obout = find_object(__DIR__"outzigai1"))
              obout = load_object(__DIR__"outzigai1");

        tell_room(obin,HIW"\n轟！轟！轟！不知道誰將石門關上了。\n"NOR);
        tell_room(obout,HIW"\n轟！轟！轟！不知道誰將石門關上了，頓時山"
                        "洞裏變得陰暗起來。\n"NOR);

        delete("exits/enter");
        delete("exits/out", obin);
        delete_temp("marks/推", obin);
        delete_temp("marks/推", obout);

        delete("long");
        set("long",@LONG
站在這裏向下望才發現自己已經離地面有十來丈高了，尋
望洞內發現四周雖都有突石，但是唯有腳下這塊能容人站在上
面觀望。仔細觀察突石周圍發現身後的石壁(bi)中竟有一絲細
小的裂縫，方才在下面看到的光亮就是從這裂縫中投射出來的。
LONG);

        return ;
}





int valid_leave(object me,string dir)
{
        me=this_player();
        
        if(dir=="down")
                return notify_fail ("這裏又沒有路，看來只有跳下去了。\n");
                 
        return 1;

}





