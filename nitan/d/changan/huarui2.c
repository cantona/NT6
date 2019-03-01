//Room: huarui2.c

inherit ROOM;

void create ()
{
        set ("short", "華瑞街");
        set("long", @LONG
華瑞街是長安城南一條東西向的大道，也是長安城的居民區。一
條碎石子舖成的街坊，南邊可見一些民居住宅，北面是一家小面館，
街頭有炊煙裊裊飄來青柴的香味。不遠處傳來家家戶戶舂米的聲音，
還有大戶人家榨香油的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju2",
                "north" : "/d/changan/mianguan",
                "west" : "/d/changan/huarui1",
                "east" : "/d/changan/huarui3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}