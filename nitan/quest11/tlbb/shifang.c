// Room: /d/shaolin/shifang.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"
void create()
{
    set("short", BLU"石坊"NOR);
    set("long", 
"一個巨大的牌坊橫架在兩片山壁之間，牌坊正上方刻着六個斗大的金字：\n"
"\n\t\t\t『"HIY"天下第一名剎"NOR"』\n\n"+
"字跡有些剝落，看上去年代頗為久遠了。前方是一偏很大的廣場，站滿了前來\n"+
"進香的香客和一些江湖上的豪士。象徵着少林寺的山門殿，就矗立在廣場的另\n"+
"一側。\n"
    );

	set("exits", ([
		"north" : __DIR__"guangchang",
		"south" : __DIR__"shijie11",
	]));

	set("outdoors", "shaolin");
	setup();
}

void init()
{
	object me = this_player();
	
	if ( me->query("sl_job")){
		me->add("job_time/少林", me->query("sl_job"));
		me->delete("sl_job");
	}
}
int valid_leave(object me, string dir)
{
  if(dir == "south" && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"zhenfa"))
  {
   tell_object(me,HIC"\n你剛要準備離開少林寺。突然一南一北兩個人影飛奔而來，竟然是少林無名僧和曾經一戰的丐幫蕭峯。\n"NOR); 
   me->move("/d/shaolin/shifang_copy");
   log_file("quest/TLBB", sprintf("%s(%s)復興天下最後一戰開始。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return notify_fail(HIR"看來這一戰，實在難免了。\n"NOR);
  }
	return ::valid_leave(me, dir);
}
