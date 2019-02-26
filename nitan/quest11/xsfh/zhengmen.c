//by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"

void create()
{
	set("short", GRN "苗家莊門口" NOR);
	set("long",@long
這裏是苗家莊的大門，兩扇黑漆漆的大門敞開着，門口正中央高懸着一塊
金色橫匾“苗家莊”，台階兩旁立着兩個石獅，只是門街冷清，頗為淒涼。
long);
  set("outdoors", "蘭州");
	set("exits",([
		"east" : __DIR__"sroad1",
		"west" : __DIR__"qianting",
]));
            set("quest",1);
	set("no_fight", 1);
	setup();
}
int valid_leave(object me, string dir)
{
    if (dir == "west" && !me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
          return notify_fail(RED"苗家莊早已經封閉，無法進去。\n"NOR);
        if(dir == "west" &&me->query_condition("killer"))
   		          return notify_fail(RED"苗家莊早已經封閉，無法進去。\n"NOR);
    return ::valid_leave(me, dir);
}

void init()
{
  object me;
  me = this_player();
  if (me->query(QUESTDIR2+"start"))
       me->start_busy(1);
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"answer")
	 &&!me->query(QUESTDIR2+"over")
     &&!me->query_temp(QUESTDIR2+"kill")
     &&!me->query_temp(QUESTDIR2+"huyidao"))
  {
     tell_object(me,YEL"突然你聽到苗家莊內好像有他人，只聽一個聲音朗聲道：“金面佛苗大俠在家麼？有朋友遠道來訪。”\n"NOR);
     tell_object(me,YEL"只聽屋中一人説道：“是哪一位朋友？恕苗人鳳眼生，素不相識。”這話聲只覺又是蒼涼，又是醇厚。\n"NOR);
     remove_call_out("goqianting");
     call_out("goqianting", 3, me);
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
   if(me->query(QUESTDIR2+"start")) return;
   shen = me->query("shen");
  if(shen <0) tell_object(me,HIR"只聽門內一個深沉渾厚的聲音傳來：看你一身邪氣，還請離開！\n"NOR);
     else tell_object(me,HIR"只聽門內一個深沉渾厚的聲音傳來：這位少俠，還請離開！\n"NOR);
}
void goqianting(object me)
{
  if(!me) return;
  if(!present(me,this_object()))
  {
      tell_object(me,HIY"你擅自離開苗家莊，錯過了精彩的一幕。\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s)初進苗家莊，卻擅自離開，失敗。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
     me->delete_temp(QUESTDIR2+"answer");
    return;
}

     tell_object(me,YEL"\n你聽到“鍾氏兄弟”、“書信”，好像是舊識，又好像是討債來的，卻聽不清楚具體在説什麼，你不由好奇心起。\n"NOR);
	   tell_room(environment(me), YEL+me->name()+"緊了緊隨身物品，緊跟着長袖飄飄，飛身躍過高牆！\n" NOR, ({me}));
           tell_object(me,RED"你一提內息，使出「一葦渡江」輕功，一翻身，越過高牆，這一手輕功當真落地無聲，確實了得。\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s)初進苗家莊。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	   me->move(__DIR__"qianting");
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

