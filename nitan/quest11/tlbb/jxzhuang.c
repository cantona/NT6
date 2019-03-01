// Room: /d/nanyang/jxzhuang.c
// Lklv Modify 2001.10.10
// Tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"

void create()
{
        set("short", "聚賢莊大門");
        set("long",
"你走到一座高宅大院的門口，大門開著，門前左右有兩個石獅子，四五級\n"
"青石台階上是兩扇釘滿銅釘的大門。看得出這裡是一大戶人家的住所。門口正\n"
"中央高懸著一塊黑底金字的大匾，匾上寫有三個大字："YEL"【聚賢莊】"NOR"。\n"
        );
		set("quest",1);
		set("outdoors", "南陽");
		set("exits", ([
			"southwest" : __DIR__"xiaolu3",
				"north" : __DIR__"dating",
		]));

		set("objects",([
			__DIR__"npc/guanjia" : 1,
				__DIR__"npc/jiading" : 1,
		]));
        
		setup();
}
void init()
{
	object obj,me = this_player();
	if ( me->query(QUESTDIR3+"start")
		&& !me->query_temp(QUESTDIR3+"kill")
		&& !me->query(QUESTDIR3+"over")){
			me->start_busy(2);
			//玩家離開這裡，離開算失敗
			obj=new(__DIR__"npc/guanjia");
			if(!present("guan jia",this_object()))
				obj->move(this_object());
			obj=new(__DIR__"npc/jiading");
			if(!present("guan jia",this_object()))
				obj->move(this_object());		
		}
}
int valid_leave(object me, string dir)
{
   object room;
   if (!(room = find_object(__DIR__"dating")))
       room = load_object(__DIR__"dating");

   if(room && room->query("busy")&& dir == "north" )
     return notify_fail(HIR"你發現聚賢莊內似乎傳來激烈的打鬥之聲，還是走為上策！\n"NOR);
   
   if (me->query(QUESTDIR3+"start") 
         && !me->query(QUESTDIR3+"over") 
         && dir == "north" 
         && present("guan jia", environment(me)))
     return notify_fail(HIR"管家冷笑一聲道：這位"+RANK_D->query_respect(me) +"請回，這裡不歡迎你！\n"NOR);
     if (me->query(QUESTDIR3+"start") 
         && !me->query(QUESTDIR3+"over") 
         && dir == "north" 
         && present("jia ding", environment(me)))
     return notify_fail(HIG"家丁冷笑一聲道：這位"+RANK_D->query_respect(me) +"請回，這裡不歡迎你！\n"NOR);

     if(dir == "north" &&(me->query_condition("killer")||	sizeof(filter_array(deep_inventory(me), (: userp :)))))
		 return notify_fail(HIY"突然從裡面傳來一陣冷笑道：這位"+RANK_D->query_respect(me) +"請回，這裡不歡迎你！\n"NOR);
     return ::valid_leave(me, dir);
}
