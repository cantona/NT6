// cool980724
// Modify By River 98/12
// COOL@SJ,9908
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空地");
	set("long", @LONG
你定了定神，看見眼前是一塊大空地，光禿禿的什麼都沒長，空地北面好
象有一間屋子,南面是你跳過來的樹牆。
LONG
	);
	set("outdoors", "大理");

	set("exits", ([
		"north" : __DIR__"muwu2",
	]));

	setup();
}

void init()
{
	object me,obj;
	me=this_player();
	if ( interactive(me)
	 && !present("duan yanqing",this_object())
	 && me->query_temp("quest/天龍八部/凌波微步篇/kill")){
		obj=new(__DIR__"npc/dyq");
	  obj->set_name("段延慶", ({ "duan yanqing", "duan","yanqing"}) );
	  obj->set("title",HIC"四大惡人"NOR);
	  obj->set("nickname",HIG"惡貫滿盈"NOR);
		obj->move(this_object());
	}
	add_action("do_jump", "jump");
	add_action("do_tiao", "tiao");
}

int do_jump(string arg)
{
	object me;
	me = this_player();
	if (!arg || arg !="wall") 
		return notify_fail("你要跳到那去？\n");
	if (random(me->query_skill("dodge",1)) < 60){ 
		write("你吸氣奮力一跳，無奈運氣不好，沒跳過樹牆，摔了下來。\n");
		write("你受了點傷!\n");
		me->add("qi", -100);
		me->add("jingli", -80);
		me->receive_wound("qi", 50);
		return 1;
	}
	else {
		write("你一吸氣，輕輕巧巧的跳過了大樹牆。\n");
		message("vision",me->name() + "一縱身跳過了樹牆。\n",environment(me), ({me}) );
		me->start_busy(1);
		me->move(__DIR__"shanlin-6");
		message("vision",me->name() + "從樹牆後面跳了過來。\n",environment(me), ({me}) );
		return 1;
	}
}

int valid_leave(object me,string dir)
{
	if( dir == "north" 
	&& objectp(present("duan yanqing", environment(me))))
		return notify_fail("段延慶擋住了路，你無法過去!\n");   
	if ( interactive(me = this_player()) 
	 && this_player()->query_temp("quest/天龍八部/凌波微步篇/kill")
	 && (dir =="north")){
		this_player()->delete_temp("quest/天龍八部/凌波微步篇/kill");
		this_player()->set_temp("quest/天龍八部/凌波微步篇/kill_duan",1);
		return 1;
	}
	return ::valid_leave(me,dir);
}
