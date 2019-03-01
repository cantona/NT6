//tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"

void create()
{
	set("short", HIC"峭壁"NOR);
	set("long", @LONG
這裡是頌摩崖之峭壁，從這裡望去，北面正是星宿一帶，南面是雁門關。
站在高處，你不由感到風光無限好。
LONG
	);
 set("no_get_from", 1); 
           set("quest",1);
 set("no_sleep_room", 1);
 setup();
}

void init()
{
	object me = this_player();
  if(me->query_condition("killer")||me->query_condition("job_busy"))
  {
     message_vision(HIC"\n突然，不知道從哪裡傳來一個聲音道：這裡不歡迎$N。\n"NOR,me); 
     tell_object(me,HIR"跟著，不知道哪裡來的一只神腳飛起一腳，將你一腳踢飛出去！\n"NOR);
     tell_room(environment(me),HIR"\n不知道哪裡來的一只神腳飛起一腳，將"+ me->name()+ "踢飛出去！\n"NOR, ({ me }));
     if(random(2)) me->move("/d/xingxiu/silk3");
     else me->move("/d/xingxiu/jyg");
     tell_room(environment(me), HIR"\n只見"+ me->name()+ "大叫一聲飛過來，摔了個狗吃屎！好帥哦~~~~~~~~\n"NOR, ({ me }));
     me->start_busy(1);
     return;
  }
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		add_action("do_look", ({"look"}));
	}
  add_action("do_jump", ({"jump", "tiao"}));
}
int do_look(string arg)
{
	object me = this_player();

	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
	 if (!arg) {
		set("long", @LONG
這裡是頌摩崖之峭壁，從這裡望去，北面正是星宿一帶，南面是雁門關。
站在高處，你不由感到風光無限好。只是側面一大片光滑之處非常奇怪。
LONG
);
		me->look(arg);
	 }
         else if (arg == "光滑之處"||arg == "側面"||arg == "cliff" ||arg == "stone") {
		tell_object(me,HIR"你仔細地觀察著峭壁，只見那一片山壁天生的平凈光滑，但正中一大片山石上卻盡是斧鑿的印痕，\n"
		                  "顯而易見，是有人故意將留下的字跡削去了。\n"NOR);
    tell_room(environment(me),HIC"\n"+me->name()+"湊近峭壁，似乎在尋找什麼。\n"NOR, ({ me }));                       
		tell_object(me,HIC"你暗暗想道：只怕這蕭峰真的是契丹人了。\n"NOR);
		me->set_temp(QUESTDIR3+"lookcliff",1);
		me->start_busy(5);
		remove_call_out("xiaofeng");
		call_out("xiaofeng",3,me);
		return 1;
	 }
	}
	else
	{
		set("long", @LONG
這裡是頌摩崖之峭壁，從這裡望去，北面正是星宿一帶，南面是雁門關。
站在高處，你不由感到風光無限好。
LONG
);
		me->look(arg);
	}		
}
void xiaofeng(object me)
{
	object obj;
	if(!me) return;
	if(!me->query(QUESTDIR3+"start")||!me->query_temp(QUESTDIR3+"lookcliff")|| me->query(QUESTDIR3+"over"))return;
  if(present("xiao feng", environment(me)))return;
  obj=new("/d/nanyang/npc/xiaofeng");
  obj->move(environment(me));	
	return;
}
int do_jump(string arg)
{
		object room,me = this_player();

    if( arg == "down" || arg == "cliff" || arg == "峭壁")
    {
		    if(me->query_skill("dodge")<200) 
	 	    {
           message_vision(HIC"\n$N吸了一口氣，嘗試跳下峭壁，卻突然發現風大山高，卻退了回來。\n"NOR,me);
           return 1;
	      }
        message_vision(HIC"\n$N吸了一口氣，一個縱身已經跳下峭壁。\n"NOR, this_player());
        if (!(room = find_object(__DIR__"silk3")))
          room = load_object(__DIR__"silk3");
        if(!room)
        { 
      	  tell_object(me,HIR"\n你無論怎麼跳，發現都還在原地!\n");
      	  log_file("quest/TLBB", sprintf("%s(%s)缺少silk.c文件。\n", me->name(1),me->query("id")) );	
        }
        else
        {
        	me->move(room);
          tell_room(environment(me),HIC"\n只見一個身影飛身而下，原來是"+me->name()+"從峭壁上跳下。\n"NOR, ({ me }));                       
        }
        return 1;
    }
    return 0;
}
