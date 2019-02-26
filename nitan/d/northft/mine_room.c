
#define CTL_MINE	__DIR__"iron_mine"

#include <mine_def.h>

inherit ROOM;

void create()
{
	set("short", "礦區");
	set("long", @LONG
這裏是一片巨大的礦區，放眼一望四處是巨大的巖石，很多
巖石上還留有被人敲砸過的痕跡，地上還散落着一些碎石頭。
LONG
	);

	setup();
}

int cmd_dig_function(object me, string arg)
{
	if(!me || (environment(me) != this_object()))
		return 0;

	if( query("qi", me) <= 20 )
		return notify_fail("你已經累的沒有一點力氣了。\n");

	message_vision("$N掄起手中的十字鎬狠狠的砸了下去。\n", me);
	me->start_busy(10);
	call_out("finish_dig", 3+random(3), me);
	return 1;
}

protected void finish_dig(object me)
{
	object stone;

	if(!me || (environment(me) != this_object()))
		return 0;

	me->stop_busy();

	if( query("qi", me) <= 20 )
	{
		tell_object(me, "你已經累的沒有一點力氣了。\n");
		return;
	}

addn("qi", -20, 	me);

	if(!random(10) || !objectp(stone = new(MINE_STONE)))
	{
		tell_object(me, "結果什麼也沒能砸下來。\n");
		return;
	}

	if(random(10))
		CTL_MINE->setup_stone(stone);

	if(!stone->move(this_object()))
	{
		destruct(stone);
		return;
	}
	message_vision(sprintf("$N敲下了一塊%s。\n", stone->name()), me);
}
