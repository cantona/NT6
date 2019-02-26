inherit ROOM;

void create()
{
        set("short", "康府大廳");
        set("long", @LONG
這裏就是康親王府的大廳，相當的寬敞明亮，四周的牆上懸掛滿
了各朝名人的真跡，正堂坐着一個衣着黃馬褂，滿面笑容的男子，那
就是當今皇上的寵臣康親王了。兩旁的座位分別坐着兩個御前侍衞，
從衣着上看來品位似乎不低。大廳往北又是一條走廊，那是通往王府
的內堂所在。
LONG );
        set("exits", ([
                "north" : "/d/beijing/kangfu_zoulang2",
                "south" : "/d/beijing/kangfu_zoulang1",
        ]));
        set("objects", ([
                "/d/beijing/npc/kangqinwang" : 1,
                "/d/beijing/npc/zhangkang" : 1,
                "/d/beijing/npc/zhaoqi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}