// Room: /suzhou/jiulou1.c
// YZC 1995/12/04 llm 99/07

inherit ROOM;

void create()
{
        set("short", "迎賓樓");
        set("long", @LONG
方圓數百裡內，迎賓樓的名氣可謂是不小。來此落腳的名士雅客
也為其題匾作詩，流下不少令其得意的東西。樓下布置簡易，顧客多
是匆匆的行人，買點包子，雞腿、米酒就趕路去了。樓上是專門舉辦
備類婚宴的喜福堂。
LONG );

        set("exits", ([
                "east" : __DIR__"baodaiqiao",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", 1100);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}