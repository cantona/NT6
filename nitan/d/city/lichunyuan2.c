// Room: /city/lichunyuan2.c
// Dec.12 1997 by Venus
inherit ROOM;
void create()
{
        set("short", "麗春院二樓");
        set("long", @LONG
你站在麗春院二樓。滿耳的淫聲穢響不絕如縷。佈置得絕對精緻
的牀上地下，突然對你產生莫名的誘惑和衝動。    幾個可憐兮兮的
千嬌百媚在點手兒招你，你想到她們可能就是昔日江湖中的眼高於頂，
頓時大為開心。
LONG );
        set("exits", ([
            "down" : "/d/city/lichunyuan",
        ]));
        set("objects", ([
            "/d/city/npc/guigong" : 1,
        ]));
	set("no_clean_up", 0);
        set("no_steal", "1");
        set("no_beg", "1");
        set("piao_room", "1");
	set("coor/x", 10);
	set("coor/y", -20);
	set("coor/z", 10);
	setup();
}
int valid_leave(object me, string dir)
{
    me = this_player();
    if (me->query_condition("prostitute"))
      return notify_fail("龜公一把抱住你：看你往哪裏逃！\n");
    else  return 1;
}