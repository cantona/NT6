//1997-3-10 by qyz
#include <room.h>
#include <ansi.h>

inherit ROOM;


void create()
{
	set("short",WHT"玄鶴洞"NOR);
	set("long",@LONG
玄鶴洞又叫仙鶴洞，處在絕壁之上，傳說洞裡有玄鶴，本是廣成子座前的仙
童，只因受命到龍門洞提取玉液瓊水，與龍宮玉女相戀，廣成子大怒，將仙童化
為玄鶴打入石洞，從此，玄鶴情綿綿，恨悠悠，蟄居不出，偶爾在雨霽和風之際
，出洞翱翔。又傳說玄鶴出洞，廣成子就要回崆峒山收徒。
LONG);
	set("exits",
	([
          "southdown" : __DIR__"xiangtou_ya",
          	]));
        set("outdoors","kongdong");
	set("objects",([
	__DIR__"npc/meihua_lu" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
void init()
{
    object me;
    me = this_player();
    if (!wizardp(me)&&!avatarp(me)&&userp(me)&&!me->query("marks/kongdong/zhou"))
    {
        message_vision("你怎麼進來的.....死去吧.....\n",me);
        me->die();
    }
    add_action("do_perform","perform");
    add_action("do_search","search");    
}

int do_search()
{
	object me=this_player();
//	if (me->query("marks/kongdong/dao"))
	{
	tell_object(me,HIG"聽罷你頓起好奇心，不由得四處打探了一番，最後你的眼光落在洞口一塊突出的巖石上。\n"NOR);
	tell_object(me,HIG"何不拿這塊巖石試試新練成的胡家刀法？\n"NOR);
	me->set("marks/kongdong/dao",2);
        return 1;              
	}
	return 0;

}

int do_perform()
{
	object me=this_player();
	object ob;
  	ob = me->query_temp("weapon");
 	if ( !ob || (string)ob->query("weapon_type") != "blade" )
	{tell_object(me,"可惜你沒有帶刀。\n");
	return 1;} 	
	if (me->query("marks/kongdong/dao")!=2)
	return 0;
	if (me->query_jibie("hujia-dao")<135)
	{tell_object(me,"你的胡家刀法修為不夠，在此處施展不開絕技。\n");
	return 1;}
	if (this_object()->query_temp("performed"))
        {message_vision("巨石已經被劈開了。\n",me);
        return 1;
	}        
	message_vision(HIB"$N看準那塊突出的巖石,暴喝一聲，使出威震八方的絕技，繞著巖石迅速劈\n出四實四虛八刀，手中的刀如同活物。\n剎那間，漫天刀光從各個方向劈向巖石。\n"NOR,me);
	if (me->query("force_factor")>450)
        message_vision(HIR"一道金石撞擊之聲過後，巨石表面應聲而裂，居然露出一面光滑的石壁來。\n",me);
        this_object()->set_temp("performed",1);
        new(__DIR__"obj/shibi")->move(this_object());       
        return 1;
}


int valid_leave(object me,string dir)
{
    if(dir=="southdown")
      message_vision("$N小心翼翼地攀巖附草，往山下爬去。\n",me);
    return ::valid_leave(me,dir);
}
