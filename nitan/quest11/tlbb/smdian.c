// Room: /d/shaolin/smdian.c
// Date: YZC 96/01/19
// by zqb

inherit ROOM;
#include <ansi.h>


void init();
void close_gate();
string look_gate();
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"


void create()
{
	set("short", HIY"山門殿"NOR);
	set("long", @LONG
這裡是少林寺的前殿山門殿。殿內青磚舖地，兩側分列哼、哈二將。身軀
雄偉，面相忿怒，頭帶寶冠，上半身裸露，手執金剛杵，一鼓鼻，一張口，露
牙睜目，兇猛可畏。兩邊各放一紅木供桌，陳列香燭，以供僧俗叩拜。北面是
一片廣場。南面是一道三丈來高的朱紅杉木包銅大門(gate)。
LONG
	);

	set("exits", ([
		"north" : __DIR__"gchang-1",
	]));

	set("item_desc",([
		"gate" : (: look_gate :),
	]));
	set("objects",([
		__DIR__"npc/zn-seng" : 2,
	]));
	setup();
}

void init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
}

void close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"guangchang")) )
		room = load_object(__DIR__"guangchang");
	if(objectp(room)){
		delete("exits/south");
			message("vision", "僧兵上前把大門關了起來。\n", this_object());
		room->delete("exits/north");
		message("vision", "乒地一聲，裡面有人把大門關上了。\n", room);
	}
}

int do_close(string arg)
{
	if (!query("exits/south"))
		return notify_fail("大門已經是關著的了。\n");

	if (!arg || (arg != "gate" && arg != "south"))
		return notify_fail("你要關什麼？\n");

	message_vision("$N朝僧兵點了點頭。\n", this_player());

	remove_call_out("close_gate");
	call_out("close_gate", 2);

	return 1;
}

int do_open(string arg)
{
	object room;

	if (query("exits/south"))
		return notify_fail("大門已經是開著了。\n");

	if (!arg || (arg != "gate" && arg != "south"))
		return notify_fail("你要開什麼？\n");

	if(!( room = find_object(__DIR__"guangchang")) )
		room = load_object(__DIR__"guangchang");
	if(objectp(room))
	{
		set("exits/south", __DIR__"guangchang");
		message_vision("$N使勁把大門打了開來。\n", this_player());
		room->set("exits/north", __FILE__);
		message("vision", "吱地一聲，裡面有人把大門打開了。\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}

	return 1;
}

string look_gate()
{
	return "一道三丈來高的朱紅杉木包銅大門。\n";
}

int valid_leave(object me, string dir)
{
	if (dir == "south") {
		if (me->id("seng bing")) return 0;
		if (me->id("mo tou")) return 0;
	}
   if(dir == "south"&&!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
  {
   message_vision(HIC"\n突然剛準備離開少林寺，$N似乎氣血有些不順，跟著腳下一個趔趄。\n"NOR,me); 
   message_vision(WHT"一個執法僧匆匆了走了過來，向$N一拱手道：“我彌陀佛，施主如此兇狠，還是留在少林潛修佛法得好。”\n"NOR,me);
   me->move("/d/shaolin/shaolinzhen");
   tell_room(environment(me), HIR"\n半空中，似乎一個人掉了下來，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({ me }));
   log_file("quest/TLBB", sprintf("%s(%s)被關進少林陣。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return notify_fail(HIR"你疑惑了一下，卻發現四周圍上一圈人，似乎是少林伏魔圈陣。\n"NOR);
  }
	return ::valid_leave(me, dir);
}
