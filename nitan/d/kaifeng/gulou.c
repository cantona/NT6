inherit ROOM;

void create()
{
        set("short", "鼓樓");
        set("long", @LONG
一座木結構的小亭閣樓，上層擺了個大鼓，是寺廟內每天晨鐘暮
鼓時所用。有一條小樓梯通向下層。閣樓的四角掛著鐵馬，隨風擺搖
著，分外動聽。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"qianyuan",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}