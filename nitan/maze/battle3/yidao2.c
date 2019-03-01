inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "城外驛道");
        set("long", @LONG
這裡是通往大宋京城的驛道，由于連年來戰火不止，顯得格外地
荒涼，不時有來往的馬匹飛奔而過，濺起一土塵煙，沿途不時有土匪
大盜出現，還是少作停留的好。
LONG );
        set("outdoors", "xiangyang");
        set("no_fly",1);

        set("exits", ([
                "east"  : __DIR__"yidao2", 
                "west"  : __DIR__"yidao2",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        if (! me->is_busy())
        me->start_busy(random(1));


        if( query_temp("yidao/mark_steps", me)>11 )
        {
         me->move(__DIR__"yidao3");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，汴樑已經近在眼前了......\n"NOR);
         return;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
         me->move(__DIR__"yidao1");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，襄陽已經近在眼前了......\n"NOR); 
         return;
        }

        tell_object(me,YEL"你快馬加鞭，一路飛馳在驛道上......\n"NOR);

}

int valid_leave(object me,string dir)
{
        object dadao,*env;
        int i,flag;
  
        env=all_inventory(environment(me));   
        flag=0;

        for(i=0;i<sizeof(env);i++)
        {
         if( objectp(env[i]) && query("id", env[i]) == "jiangyangdadao"
             && query("killer", env[i]) == query("id", me) )
         flag=1;
        }

        if( query_temp("warquest/purchase", me) && random(12)>10 )
        {
                dadao=new(__DIR__"npc/dadao");
                dadao->set_from_me(me);
                set_temp("warquest/party", "meng", dadao);
                dadao->move(environment(me));
                dadao->kill_ob(me);
                me->kill_ob(dadao);
        return notify_fail("忽然從路邊叢林中殺出一路人馬！\n");
        } else
        if(flag)
        return notify_fail("江陽大盜擋住了你的去路。\n");

       if( dir == "east" )
       addn_temp("yidao/mark_steps", -random(2), me);
       if(  dir == "west" )
       addn_temp("yidao/mark_steps", random(2), me);
       return ::valid_leave(me,dir);
}
