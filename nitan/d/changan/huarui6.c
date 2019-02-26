//Room: huarui6.c

inherit ROOM;

void create ()
{
        set ("short", "華瑞街");
        set("long", @LONG
華瑞街是長安城南一條東西向的大道，也是長安城的居民區。一
條碎石子鋪成的街坊，南邊可見一些民居住宅，街頭有炊煙裊裊飄來
青柴的香味。不遠處傳來家家户户舂米的聲音，還有大户人家榨香油
的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju6",
                "north" : "/d/changan/tuchangguan",
                "west" : "/d/changan/huarui5",
                "east" : "/d/changan/liande-nankou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10690);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}