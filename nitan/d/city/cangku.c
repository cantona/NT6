// Room: /city/cangku.c

inherit ROOM;
void init();

void create()
{
	set("short", "倉庫");
        set("long", @LONG
這裏是一間黑黝黝的倉庫，堆滿了唐家的各種雜物，塞了滿滿一
倉庫。看來你是被人拐賣到這裏來的。
LONG );
	set("valid_startroom", "1");
	set("no_fight", 1);
//	set("no_clean_up", 0);

	set("objects", ([
		"/d/city/obj/jitui" : 3,
		"/d/city/obj/jiudai" : 1,
	]));
	setup();
}

void init()
{
	object ob;

	ob = this_player();
set("startroom", "/d/city/cangku", 	ob);
set_temp("selled", 1, 	ob);
}