// Room: fatang2.c
// tangfeng@SJ 2004

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "法堂二樓");
	set("long", @LONG
這裏是大輪寺掌門居所，四面清幽，修禪證道最妙不過。真是：
    戲招西塞山前月，來聽東林寺裏鍾。
    悠然萬慮忘，有此一樓足。
    西窗外，羣山萬壑，望盡天地。
    東窗外，樓台錯落，幾盡悠閒。
LONG
	);

	set("exits", (["down" : __DIR__"fatang",]));
        set("objects", ([CLASS_D("xueshan") + "/jiumozhi" : 1,]));
	setup();
}
void init()
{
        add_action("do_push", "push");
        add_action("do_look", "look");
}
int do_look(string arg)
{
	object me = this_player();

	if (!me->query_temp("quest/天龍八部/天龍營救篇/askzhi")) {
		set("long", @LONG
這裏是大輪寺掌門居所，四面清幽，修禪證道最妙不過。真是：
    戲招西塞山前月，來聽東林寺裏鍾。
    悠然萬慮忘，有此一樓足。
    西窗外，羣山萬壑，望盡天地。
    東窗外，樓台錯落，幾盡悠閒。
LONG
);
		me->look(arg);
	}
	else {
		if (!arg) {
			set("long", @LONG
這裏是大輪寺掌門居所，四面清幽，修禪證道最妙不過。真是：
    戲招西塞山前月，來聽東林寺裏鍾。
    悠然萬慮忘，有此一樓足。
    西窗外，羣山萬壑，望盡天地。
    東窗外，樓台錯落，幾盡悠閒。
    
只是你仔細地觀察着四周，發現北面牆邊（wall）似乎隱有活動。
LONG
);
			me->look(arg);
		}
		else if (arg == "wall") {
			tell_object(me,HIR"你仔細地觀察着四周，發現牆邊可以推開（push）。\n"NOR);
			return 1;
		}
 }		
}

int do_push(string arg)
{
		object me = this_player();
    if (!me->query_temp("quest/天龍八部/天龍營救篇/askzhi")) return 0;
	      if( arg == "wall" || arg == "牆" || arg == "牆邊")
        {
        message_vision("$N推開這堵牆，發現了向北通向一個暗室。\n", this_player());
        if( !query("exits/north") ) {
        set("exits/north", __DIR__"anshi");
        remove_call_out("close_path");
        call_out("close_path", 15);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/north") ) return;
        message("vision","一會會，嗵的一聲，牆又恢復原樣。\n", this_object() );
        delete("exits/north");
}
int valid_leave(object me, string dir)
{
     if (dir == "north" && present("jiumo zhi", environment(me)))
     return notify_fail("鳩摩智喝道：亂走什麼，這位大師請回！\n");    
     if (dir == "north" && me->query_condition("killer"))
     return notify_fail("你發現似乎有股神力維護那裏，你無法進入！\n");
     return ::valid_leave(me, dir);
}
