//Room: huarui4.c

inherit ROOM;

void create ()
{
        set ("short", "華瑞街");
        set("long", @LONG
華瑞街是長安城南一條東西向的大道，也是長安城的居民區。一
條碎石子舖成的街坊，南邊可見一些民居住宅，北面是小鏡湖，街頭
有炊煙裊裊飄來青柴的香味。不遠處傳來家家戶戶舂米的聲音，還有
大戶人家榨香油的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju4",
                "north" : "/d/changan/xiaojinghu",
                "west" : "/d/changan/nanan-daokou",
                "east" : "/d/changan/huarui5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}