// houting.c
inherit ROOM;
void create()
{
	set("short", "神龍教後廳");
	set("long", @LONG
這是神龍教的議事場所--潛龍廳。此廳較小，前面有兩張大竹椅，
兩邊擺着五個小凳，看來是神龍教五龍使平時所坐的位置。
LONG );
	set("exits", ([
		"south" : __DIR__"dating",
	]));

	set("objects", ([
		CLASS_D("shenlong")+"/yin": 1,
	]));
	set("outdoors","shenlong");
	setup();
	replace_program(ROOM);
}
