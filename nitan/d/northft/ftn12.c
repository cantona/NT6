// Room: /d/northft/ftn12.c

inherit ROOM;

protected int open, count;
protected object mob;

protected object query_mob()
{
	if(!mob)
		mob = find_object(__DIR__"stone");
	if(!mob)
		mob = load_object(__DIR__"stone");

	return mob;
}

string query_long()
{
	object ob = query_mob();

	if(!ob || ob->query_open())
		return "這是一條窄窄的上山小路，兩旁怪石嶙峋，中間的路倒是很
平坦，看樣子是被人專門開掘出來的。\n";
	else
		return "這是一條窄窄的上山小路，兩旁怪石嶙峋，中間的路倒是很
平坦，看樣子是被人專門開掘出來的。路中央一塊大石頭擋住了
向西的去路。\n";
}

mapping query_desc()
{
	object ob = query_mob();

	if(ob && !ob->query_open())
		return ([
"石頭" : "這是一塊大青石頭，不知道能不能推(push)開。\n",
"大石頭" : "這是一塊大青石頭，不知道能不能推(push)開。\n",
]);

	else
		return 0;
}

void create()
{
	set("short", "山路");
	set("long",  (: query_long :));
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"ftn13",
]));

	set("item_desc", (: query_desc :));

	set("outdoors", "northft");
	setup();
}

void init()
{
	add_action("do_push", "push");
}

int do_push(string arg)
{
	object ob = query_mob(), me = this_player();

	if( !ob || ob->query_open() || ((arg != "石頭") && (arg != "大石頭")) )
		return 0;

	message_vision("$N雙膀一較力，使勁推了一下大石頭。\n", me);
	ob->do_push(me);

	return 1;
}
