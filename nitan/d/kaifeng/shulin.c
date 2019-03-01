inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
一片雜樹林，落葉掉了滿地，斑駁的枝葉顯露出天氣的無情。綠
色的小草就從樹之間的空隙長出來。林中點點的都是綠色。小路穿過
樹林不遠就是禹王台。西面是中州方向。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "northwest" : __DIR__"dadao1",
                "east" : __DIR__"yuwang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}