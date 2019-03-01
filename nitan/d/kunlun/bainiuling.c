// Room: /d/kunlun/bainiuling.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_wo(string arg);
int do_breathe();
void delete_done(object me);

void create()
{
        set("short", "白牛嶺");
        set("long",@long
這座山嶺因終年覆蓋白雪，且形狀遠望猶如一頭正在吃草的牛而得
名。這裡寒風呼嘯，凜冽刺骨，你不禁打了個寒顫。山頂有一處平地，
放有一塊青色的巨石(stone)。
long);
        set("exits",([
                "southwest" : __DIR__"fufengshan",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "stone" :"這塊巨石很大，可以躺下一個人。表面十分平整光滑，似乎常有人摩挲。\n",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119970);
        set("coor/y", 40180);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_wo", "wo");
        add_action("do_breathe", "breathe");
}

int do_wo(string arg)
{
        if ( !arg || (arg != "stone") )
        return notify_fail("你要臥在什麼上面？\n");

        if (this_player()->is_busy())
                return notify_fail("你正忙著呢。\n");

        if( query_temp("marks/wo", this_player()) )
                return notify_fail("你已經躺在青石上了。\n");

        set_temp("marks/wo", 1, this_player());
        return notify_fail("你側身躺于青石上，意守丹田，口眼輕閉，雙腿自然微曲，全身放鬆。\n");
}

int do_breathe()
{
        object me=this_player();

        if( !query_temp("marks/wo", me) )
                return notify_fail("你深深吸了幾口氣，只覺得寒氣沖進五臟六腑，體內的真氣幾乎提不起來。\n");

        if (me->is_busy())
                return notify_fail("你正忙著呢。\n");

        if( query_temp("marks/done", me) )
                return notify_fail("寒風凜冽，你剛運過功，身子正十分虛弱，先好好休息一下吧。\n");

        if (me->query_skill("liangyi-shengong", 1) < 120 ) 
                return notify_fail("你內功基底太弱，不可以隨意控制內息。\n");
                
        if (me->query_skill("liangyi-shengong", 1) > 199 ) 
                return notify_fail("你的兩儀神功已經很強了，無法再通過吐納來增強功力。\n"); 
                
        if (! me->can_improve_skill("liangyi-shengong")) 
                return notify_fail("你的實戰經驗不足，無法繼續吐納練功。\n"); 

        if (query("qi", me) < 40 || query("jing", me) < 40) 
                return notify_fail("你現在已經很疲倦了，休息一下再來吧息。\n"); 

        message_vision(HIW "\n$N" HIW "集聚體內的兩儀真氣，深深吸進幾口氣，又緩緩的將" 
                       "其呼出\n體外。$N" HIW "只覺得全身透徹清涼心定似水，仿佛已物我" 
                       "渾然一體。\n\n" NOR, me); 

        me->receive_damage("jing", random(30));
        me->receive_damage("qi",   random(30));
        if (me->can_improve_skill("liangyi-shengong")) 
                me->improve_skill("liangyi-shengong", 5 + query("int", me) / 2 + 
                                  me->query_skill("force") / 6); 

        set_temp("marks/done", 1, me);
        call_out("delete_done", 5, me);

        return 1;
}

void delete_done(object me)
{
        if( objectp(me))delete_temp("marks/done", me);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/wo", me);
        return ::valid_leave(me, dir);
}
