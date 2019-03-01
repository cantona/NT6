//by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"

void create()
{
	set("short",HIW "前廳" NOR);
	set("long", @LONG
這是苗家莊的前廳，由于修建年代久遠，看起來已頗為陳舊，但因頗為幹
凈完全沒有陳年舊宅的陰晦之氣。
LONG);
	set("exits", ([
	  "east" : __DIR__"zhengmen",
	  "north" : __DIR__"zhenting",
]));
            set("quest",1);
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  if (me->query(QUESTDIR2+"start")
 		 &&!me->query_condition("killer")
		  &&!me->query(QUESTDIR2+"over")
		  &&!me->query_temp(QUESTDIR2+"have_kill")//增加一個標記（原來的有點亂了）
     &&me->query_temp(QUESTDIR2+"answer")
     &&!me->query_temp(QUESTDIR2+"huyidao")
     &&!me->query_temp(QUESTDIR2+"kill"))
  {
     tell_object(me,HIC"你身子還尚在空中，突然你聽到“啊喲！”你咋以為自己身形被發現，不料卻是苗人風發出痛苦之聲，你偷眼一看，大吃一驚。”\n"
                       "地上一封破亂的書信，苗人風雙手揉眼，臉現痛苦之色。在這一霎之間，你心中已然雪亮。那黑衣人眼見逃走，你奪路攔截。\n"NOR+
                    RED"“狗賊休走！”"NOR+HIC"你飛身向那黑衣人撲去，猛覺背後風聲勁急，一股剛猛無比的掌力直撲自己背心，只得雙掌反擊，運力相卸。\n"NOR);
     message_vision(HIR"\n$N飄然落地，只見前廳裡站著三個黑衣人，聽到一個黑衣人喊道：並肩一起上。\n"NOR, me);
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     remove_call_out("killme");
     call_out("killme", 5, me);
    }
}
void killme(object me)
{
	object obj;
  if(!me) return;

  if (me->query(QUESTDIR2+"start")
 		 &&!me->query_condition("killer")
 		  &&!me->query_temp(QUESTDIR2+"have_kill")//增加一個標記（原來的有點亂了）
     &&me->query_temp(QUESTDIR2+"answer")
     &&!me->query_temp(QUESTDIR2+"huyidao")
     &&!me->query_temp(QUESTDIR2+"kill"))
  {
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     tell_object(me,HIG"\n\n哪裡來的三個好手，只是行事為何如此卑鄙。不知道苗大俠傷勢如何，當務之急還是盡快解決眼前敵人。\n"NOR);
     message_vision(HIC"$N聽到兵刃劈風之聲襲向頭頂，中間夾著鎖鏈扭動的聲音，知是三節棍、鏈子槍一類武器，$N右手倏地伸出，抓住那$n的三節棍的棍頭一抖。\n"NOR, me,obj);
     message_vision(HIC"那$n“啊”的一聲，手臂酸麻，三節棍已然脫手，$N順手揮出，拍的一響，擊在$p腰眼之上。$n立時閉氣，暈了過去。\n\n"NOR, me,obj);
     obj->unconcious();
  }
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n黑衣人大聲喝道：哪裡走。一把攔住你，你竟然無法離開。\n"NOR);
       if (present("heiyi ren",this_object()))
                return notify_fail(RED"\n黑衣人大聲喝道：哪裡走。一把攔住你，你竟然無法離開。\n"NOR);
   		if(me->query_condition("killer"))
   		          return notify_fail(RED"\n怎麼進來的？？這裡等wiz吧。\n"NOR);
        return ::valid_leave(me, dir);
}

