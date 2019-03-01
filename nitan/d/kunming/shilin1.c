inherit ROOM;

void create()
{
        set("short", "阿詩瑪");
        set("long", @LONG
這裡是石林著名的阿詩瑪峰，相傳很就以前，美麗的哈尼
族姑娘阿詩瑪在此等侯他的阿黑哥，然而阿黑卻被地主老財殺
害了，阿詩瑪等啊等，始終沒有等來心愛的情郎，終究化作了
一座石峰，永遠的守侯下去。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "north" : __DIR__"shilin", 
                "west"  :__DIR__"shilin2",
        ]));
        set("objects", ([
                "/d/wudu/npc/youngboy" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}