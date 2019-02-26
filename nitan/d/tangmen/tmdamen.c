//tmdamen.c

inherit ROOM;
#include <ansi.h>;

int do_qu(string arg);
string look_bian();

void create()
{
        set("short","蜀中唐門");
        set("long",
"一座宏偉建築，一堵裏許長的紅牆，一個鎦金的大匾(bian)。好大的\n"
"氣派，一股敬意油然而生，這就是蜀中唐門的門樓了。但這裏冷冷清清的，\n"
"好像沒有多少人來過這裏。也許是唐門人不在江湖走動的原因吧。門口站\n"
"着幾個唐門的弟子。\n"
);
        set("outdoors", "tangmen");
        set("item_desc", ([
             "bian"  : (: look_bian :),
            ])); 
        set("exits", ([ 
            "enter"    : __DIR__"qianyuan",
            "southeast"    : __DIR__"gudao2",
        ]));
        set("objects", ([
            __DIR__"npc/tanggang" : 1,
            __DIR__"npc/dizi" : 2,
        ]));    
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_qu","qu");
}
        
string look_bian()
{
        object me;
        me = this_player();
        
        
        if( query("tangmen/yanli", me)>99 && !query_temp("dongdong", me) )
        {
               
              set_temp("dongdong", 1, me);
              return HIC"匾後面好像有一個東西! 你可以取下來看看。\n"NOR;
        }
        
        return "四個鎦金大字："+HIY"蜀 中 唐 門 \n"NOR;
                  
}

int do_qu(string arg)
{
        object me,ob;
        
        me = this_player();
        
        if( !query_temp("dongdong", me))return 0;
        
        if( query_temp("qudong", me) )
               return notify_fail(HIR"心不要太黑啊！\n"NOR);
        
        if ( !arg || arg != "dongxi")
               return notify_fail("你想取什麼啊！\n");
               
        if ( me->query_skill("dodge") < 120 )
               return notify_fail(HIR"你的身手太差了！\n"NOR);
               
        delete_temp("dongdong", me);
        ob = new("/kungfu/class/tangmen/obj/jie");
        tell_object(me,HIG"你得到了一件暗器。\n"NOR);
        set_temp("qudong", 1, me);
        ob->move(me);
        return 1;
}
/*
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("tang gan", this_object())))
                return 1;

        if (dir == "enter")
                return guarder->permit_pass(me, dir);

        return 1;
}
*/

int valid_leave(object me, string dir)
{

        if ( dir == "enter" && objectp(present("tang gang", environment(me))))
        {
                if( !query("family", me) )
                {
                        return notify_fail( "這位"+RANK_D->query_respect(me)+"要學藝的話到鎮上找唐柔？\n");
                }
                if( query("family/family_name", me) != "唐門世家" )
                {
                        return notify_fail( "這位"+RANK_D->query_respect(me)+"，你已是武林中人，不知到此有何干！\n");  
                }    
                if( query("tangmen/upshan", me) )
                {
                        if( query("betrayer", me) )
                        {
                                tell_object(me,"唐剛説道：“你這個可恥的傢伙！”\n");
                                return 0;
                        }
                        else 
                        {
                                tell_object(me,"唐剛説道：進去吧！\n");
                                me->move("/d/tangmen/qianyuan");
                                return 1;
                        }
                }                       
                else  return notify_fail("你的武功還沒有練到家，不可進唐門的！\n");
        } else 
        if ( dir == "enter" )
        {
                if( !query("family", me) || query("family/family_name", me) != "唐門世家" || 
                     !query("tangmen/upshan", me) )
                        return notify_fail("你一抬足，發現地上有毒，忙抽腿退回。\n");                        
        }               
        return ::valid_leave(me, dir);
}
