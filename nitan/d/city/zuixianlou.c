// Room: /city/zuixianlou.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "醉仙樓");
        set("long", @LONG
方圓數百裡內提起醉仙樓可以說是無人不知，無人不曉。當年蘇
學士雲遊到此，對醉仙樓的花雕酒讚不絕口，欣然為其題匾，流下一
段傳遍海內的佳話，從此醉仙樓名聲大震。樓下布置簡易，顧客多是
匆匆的行人，買點包子、雞腿、米酒就趕路去了。樓上是雅座。
LONG );
	set("exits", ([
		"west" : "/d/city/beidajie2",
		"up" : "/d/city/zuixianlou2",
	]));
	set("objects", ([
		"/d/city/npc/xiaoer2" : 1,
        "/adm/npc/kuangfeng" : 1,
	]));
        set("no_fight", 1);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}