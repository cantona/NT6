//1997-3-10 by qyz
#include <room.h>
#include <ansi.h>

inherit ROOM;


void create()
{
	set("short","疑無路");
	set("long",@LONG
在光滑的崖壁上，垂下來一條三丈餘長的鐵索梯，黑黝黝，山風吹起不時地
擺動，撞在石壁上發出錚錚鏘鏘的響聲，令人不寒而栗。崖頂又是一條長長的天
橋棧道，一面臨崖，一面懸空，用鋼□釘入崖壁，其上架些木板，十分險峻，下
腳稍重，木板另一頭就翹起，把人嚇得喪魂失魄。所以除了修為很深的真人，誰
也不敢爬上崖壁去。
LONG);
	set("not_startroom",1);
	set("exits",
	([
             "down" : __DIR__"xianren_qiao",
//             "up" : __DIR__"xuanhe_dong",
          	]));
        set("outdoors","kongdong");
	set("objects",([
		__DIR__"npc/zhou" : 1,
		]) );
        setup();
        //place_program(ROOM);
}
void init()
{
	add_action("do_climb","climb");
	add_action("do_update","update");	
	}
int do_update()
{return 1;}
int do_climb(string arg)
{
        object *all;
                int i;
	object me =this_player();
	
	if(!arg||arg!="棧道")
	return notify_fail("你要往哪裡去？可不是鬧著玩的！\n");
	if(me->query_temp("climbing"))
	return notify_fail("你正在戰戰兢兢地過棧道呢！\n");

       all=all_inventory(me);
            for(i=0;i<sizeof(all);i++)
                if(userp(all[i])){
                    message_vision("$N把$n往地下一摔，勇敢的跳了下去。\n",me,all[i]);
                    all[i]->move("/d/menpai/kongdong/yiwu_lu");
                }        
    me->start_busy(30,"性命攸關哪\n");
	call_out("pashan", 5, me, 0);
	me->set_temp("climbing",1);
        message_vision( HIG"$N深深吸了幾口氣，沿著顫顫悠悠的棧道走了過去......\n"NOR ,me);
	return 1;

}
	
void pashan( object me, int number )
{
	object *inv;
int i,j;
object dong =load_object(__DIR__"xuanhe_dong");  
i=number + 1;
switch( i ) {
case 1:
case 2:
case 3:
case 4:
message_vision( HIR"$N慢慢地一步一步地往前挪......\n"NOR ,me);
break;
case 5:
message_vision( HIG"眼看$N已經到了棧道中央了......\n"NOR,me );
break;
case 6:
case 7:
case 8:
case 9:
message_vision( HIR"$N慢慢地一步一步地往前挪......\n"NOR ,me);
break;
default:
if( !random(7)&&me->query("id")=="zhou zhenren" && !present("zhou zhenren",dong))
{
message_vision( HIG"終于，$N到達了對面的石壁....好險呀！\n",me);
me->move("/d/menpai/kongdong/xuanhe_dong");
inv = all_inventory(this_object());
for (j = 0; j < sizeof(inv); j++)
  if (userp(inv[j]))
  inv[j]->set("marks/kongdong/zhou",1);
return;	
	}
message_vision( HIY"突然一個踉蹌，$N歪向一邊，晃了兩晃就掉了下去.....\n"NOR, me);
if( me->query_xiuwei("dodge")>3200&&present("zhou zhenren",dong)&&random(me->query_kar())>28)
{message_vision( HIG"石壁對面的周真人拋出一道鐵索，正好纏在$N的腰間，把$N救了上去....好險呀！\n"NOR,me );
me->move("/d/menpai/kongdong/xuanhe_dong");
}
else
{message_vision( HIY"只聽$N一身慘叫，已墜下萬丈深淵......\n"NOR,me);
me->set("eff_sen",me->query("eff_sen")/2);
me->move(__DIR__"xiangtou_ya");
me->delete_temp("climbing");
if(!userp(me))
destruct(me);
else if(me->query("eff_sen")<me->query("max_sen")/6)
me->die();
else
me->unconcious();
}
return;
}
call_out( "pashan", 5, me, i );
return;
}
/*
int valid_leave(object me,string dir)
{
    if(dir=="up")
      return notify_fail("只有爬過棧道才能走過去的，可以嘗試(climb 棧道)。\n");
    return ::valid_leave(me,dir);
}
*/