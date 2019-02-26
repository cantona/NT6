//Created by Redhat@Sjmud 2009/4/7

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射鵰英雄傳/風雪驚變/"

void create()
{
	set("short", GRN "前院" NOR);
	set("long",@long
這裏是楊鐵心家的前院，院子由籬笆和竹子編成的柵欄，院子裏放着一個鐵犁，顯得格外蒼涼。
long);
  set("outdoors", "蘭州");
	set("exits",([
		"north" : __DIR__"yangjia",
		"south" : __DIR__"njroad3",
]));
            set("quest",1);
	set("no_fight", 1);
	setup();
}
int valid_leave(object me, string dir)
{
    if (dir == "north" && !me->query(QUESTDIR+"over"))
          return notify_fail(RED"沒有主人的允許你不可以去人家家裏。\n"NOR);
        if(dir == "north" &&me->query_condition("killer")) 
   		          return notify_fail(RED"沒有主人的允許你不可以去人家家裏。\n"NOR);
    return ::valid_leave(me, dir);
}

void init()
{
  object me;
  me = this_player();
  if (me->query(QUESTDIR+"start"))
       me->start_busy(1);
  if (me->query(QUESTDIR+"start")
	   &&!me->query(QUESTDIR+"over")
     &&!me->query_temp(QUESTDIR+"kill"))
  {
     tell_object(me,YEL"只聽得眾兵丁齊聲叫喊：“捉拿反賊，莫讓反賊逃了！””\n"NOR); 
     tell_object(me,YEL"忽聽一名武將高聲叫道：“郭嘯天、楊鐵心兩名反賊，快快出來受縛納命。”\n"NOR);       
     remove_call_out("goyangjia");
     call_out("goyangjia", 3, me);      
     write(CYN"\n你不由感到十分好奇，你停了下來，靜靜傾聽。\n"NOR);
  } 
  else
  {  
  remove_call_out("greeting");
  call_out("greeting", 4, me);   
  }
	add_action("do_save", "save");
	add_action("do_quit", "quit");
}
void greeting(object me)
{
    int shen;
  if(!me) return;
   if(!present(me,this_object())) return;
   if(me->query(QUESTDIR+"start")) return;
   shen = me->query("shen");
  if(shen <0) tell_object(me,HIR"只聽門內一個深沉渾厚的聲音傳來：看你一身邪氣，還請離開！\n"NOR);
     else tell_object(me,HIR"只聽門內一個深沉渾厚的聲音傳來：這位少俠，還請離開！\n"NOR);
}
void goyangjia(object me)
{
  if(!me) return;
  if(!present(me,this_object()))
  {
      tell_object(me,HIY"你擅自離開牛家村楊家前院，錯過了精彩的一幕。\n"NOR);
        log_file("quest/SheDiao", sprintf("%s(%s)初進牛家村楊家前院，卻擅自離開，失敗。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
     me->delete_temp(QUESTDIR+"start");
    return;
}

     tell_object(me,YEL"\n你聽到楊鐵心低説道：“官家不知為了何事，竟來污害良民。跟官府是辯不清楚的，咱們只好逃命。你別慌，憑我這杆槍，定能保你衝出重圍。”\n"NOR); 
	   tell_room(environment(me), YEL+me->name()+"一想大俠楊鐵心要突受危難，猛然衝進楊家去救楊鐵心！\n" NOR, ({me}));
        log_file("quest/SheDiao", sprintf("%s(%s)初進牛家村楊家前院。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	   me->move(__DIR__"yangjia");  
}
int do_save()
{
	write("這裏不準存盤！\n");
	return 1;
}
int do_quit()
{
	write("這裏不準退出！\n");
	return 1;
}

