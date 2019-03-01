#include <room.h>
#include <ansi.h>
inherit ROOM;
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
void create()
{
         set("short", HIC"瀾滄江邊"NOR);
         set("long",@LONG
你沿著山坡走到瀾滄江邊，朝陽初升，照得碧玉般的江面上猶如鑲了一層
黃金一般，壯麗無比，你站在這裡，心中什麼也不願意想，只希望就這樣天長
地久，時間永恆。
LONG
 );

        set("exits",([
             "eastup" : __DIR__"gaoshan",
]));
        
	set("outdoors", "大理");
	setup();
}

void init()
{
	object me = this_player();
      
	if (me->query_temp(QUESTDIR1+"yingjiu")&& me->query(QUESTDIR1+"pass_shanlu")) {
		me->set_temp("wait", 1);
		tell_object(me,HIC"\n你悄立江邊，思湧如潮，心中思緒萬千。\n"NOR);
		call_out("do_wait", 20 + random(10), me);
	}
	add_action("do_jump", "jump");
	add_action("do_look", "look");
}

void do_wait(object me)
{

if(!me) return;
	if(environment(me) && me->query_temp("wait")) {
		tell_object(me,HIY"\n你悄立江邊，思湧如潮，心中思緒萬千。突然眼角瞥處，見數十丈外一塊大巖石（yan)上似乎有些古怪。\n"NOR);
		me->delele_temp("wait");
		me->set_temp("yan1",1);
	}
}

int do_look(string arg)
{
	object me = this_player();

	if (!me->query_temp("yan1")) {
		set("long", @LONG
你沿著山坡走到瀾滄江邊，朝陽初升，照得碧玉般的江面上猶如鑲了一層
黃金一般，壯麗無比，你站在這裡，心中什麼也不願意想，只希望就這樣天長
地久，時間永恆。
LONG
);
		me->look(arg);
	}
	else {
		if (!arg) {
			set("long", @LONG
你沿著山坡走到瀾滄江邊，朝陽初升，照得碧玉般的江面上猶如鑲了一層
黃金一般，壯麗無比，你站在這裡，心中什麼也不願意想，只希望就這樣天長
地久，時間永恆。你悄立江邊，思湧如潮，心中思緒萬千。突然眼角瞥處，見
數十丈外一塊大巖石（yan)上似乎有些古怪。
LONG
);
			me->look(arg);
		}
		else if (arg == "rock" || arg == "yanshi" || arg == "yan") {
			tell_object(me,HIR"一塊巨巖，不知道可不可以跳上去？\n"NOR);
			me->set_temp("yan2", 1);
			return 1;
		}
       }		
}

int do_jump(string arg)
{
	object me;
	me = this_player();

	if (arg !="yan"|| !me->query_temp("yan2")) 
		return notify_fail("你要跳到那去？\n");

	if (me->query_skill("dodge",1) < 80)
		tell_object(me,WHT"你打量了下巖石和你之間的距離，似乎太遠了，只好做罷。\n"NOR);
	else {
		tell_object(me,HIR"你一提氣，縱身跳到了巖石上。\n"NOR);
		message("vision", me->name() + "一縱身跳到了幾十丈遠的大巖石上。\n", environment(me), ({me}) );
		me->delete_temp("wait");
		me->delete_temp("yan1");
		me->delete_temp("yan2");     
		me->move(__DIR__"yan");
		message("vision", me->name() + "從下面躍了上來。\n", environment(me), ({me}) );
	}
	return 1;
}

int valid_leave(object me,string dir)
{
	if (me->query_temp("wait"))
		me->delete_temp("wait");
	me->delete_temp("yan1");
	me->delete_temp("yan2");     
        return ::valid_leave(me,dir);
}
