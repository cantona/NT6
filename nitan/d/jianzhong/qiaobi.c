#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","峭壁");
        set("long",@LONG
這個峭壁有如一座極大的屏風，沖天而起，峭壁中央離
地約二十餘丈處，生着一塊三四丈見方的大石，便似一個平
台，石上隱隱刻得有字。極目望去，是「劍冢」二字。峭壁
上每隔數尺就生着一叢青苔，不知道如何形成的。
LONG
        );
        set("exits",([
                "west":__DIR__"donghou1",
                "south":__DIR__"donghou1",
                "east":__DIR__"donghou1",
        ]));
        set("outdoors", "jianzhong");
        set("coor/x", -401);
        set("coor/y", -421);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_climb","climb");
        add_action("do_wa","wa");
        add_action("do_wa","挖");
        add_action("do_wa","dig");
}

int do_climb(string arg)
{
        object me=this_player();
        if((arg=="青苔")||(arg=="qingtai")) return notify_fail("青苔這麼滑，如何能爬？\n");
        if((arg!="峭壁")&&(arg!="bi")&&(arg!="qiaobi")) return notify_fail("你要爬什麼？\n");
        if( !query("dig_qingtai", this_object()) || (query("dig_qingtai", this_object()) == 0) )
                return notify_fail("峭壁上長滿青苔，不先挖去，如何能爬？\n");
        message_vision("$N順着挖出的二十來個小坑，嘗試着向峭壁上爬去。\n",me);
        me->start_busy(1);
        call_out("check_trigger",1,me);
        return 1;
}
void check_trigger(object me)
{
        object room;
       if( !(room = find_object(__DIR__"qiaobi1")) )        
                room = load_object(__DIR__"qiaobi1");
        if( room = find_object(__DIR__"qiaobi1") ) 
        {
                if( query("climb_trigger", room) == 0 )
                {
                        message_vision("$N在峭壁上越爬越高……\n",me);
                        set("climb_trigger", 1, room);
                        me->move(room);
                        call_out("check_dodge",0,me,room);
                }        else        write("峭壁上有人正在攀登。\n");
        
        }
}
void check_dodge(object me,object room)
{
        if( (query("combat_exp", me)<50000) || (me->query_dex()<30) )
        {
                message_vision(HIR"一陣大風吹來，$N沒有抓牢，一下子從峭壁上摔了下來……\n"NOR,me);
                me->move(__DIR__"qiaobi");
                set("climb_trigger", 0, room);
                message("vision",query("name", me)+"突然從峭壁上摔了下來。\n",environment(me),me);
                if( (int)me->query_skill("dodge",1) > 50 )
                        me->unconcious();
                else 
                {
                        set_temp("last_damage_from", "從懸崖摔下來", me);
                        me->die();
                }
        } else
        if( (query("combat_exp", me)<100000) || (me->query_dex()<32) )
        {
                message_vision(HIY"一陣大風吹來，$N只覺得自己頭昏眼花，搖搖欲墜，只好原路爬回。\n"NOR,me);
                me->move(__DIR__"qiaobi");
                set("climb_trigger", 0, room);
                message("vision",query("name", me)+"垂頭喪氣從峭壁上爬了下來。\n",environment(me),me);
                me->receive_damage("qi",80);
                me->receive_damage("jing",50);
        } else 
        {
                message_vision(HIC"一陣大風吹來，把$N的衣角吹得「咧咧」直響，可$N在峭壁上紋絲不動。\n"NOR,me);
                me->start_busy(1);
                call_out("climb_finish",1,me,room);
        }
}
void climb_finish(object me,object room)
{
        message_vision("$N稍吸了口氣，又繼續向上爬，一邊爬一邊挖去上面小坑中的青苔。\n",me);
        me->move(__DIR__"jianzhong");
        set("climb_trigger", 0, room);
        message("vision","你終於爬上了峭壁上的「劍冢」。\n",me);
        message("vision",query("name", me)+"從峭壁下爬了上來。\n",environment(me),me);
}
int do_wa(string arg)
{
        if((arg!="qingtai")&&(arg!="青苔"))
                return notify_fail("你要挖什麼？\n");
        if( query("dig_qingtai", this_object())>0 )
                return notify_fail("有人已經挖過了。\n");
        message("vison","你把峭壁上較低的青苔都用手挖去了。\n",this_player());
        message("vison",query("name", this_player())+"把峭壁上較低的青苔都用手挖去了。\n",environment(this_player()),this_player());
        set("dig_qingtai", 1, this_object());
        return 1;
}