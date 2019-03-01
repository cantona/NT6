//Room: huarui1.c

inherit ROOM;

void create ()
{
        set ("short", "華瑞街");
        set("long", @LONG
華瑞街是長安城南一條東西向的大道，也是長安城的居民區。一
條碎石子舖成的街坊，南邊可見一些民居住宅，街頭有炊煙裊裊飄來
青柴的香味。不遠處傳來家家戶戶舂米的聲音，還有大戶人家榨香油
的醇香味。路邊三五個小孩正在拍手唱歌玩耍著。　　
LONG );
        set("exits", ([
                "north" : __DIR__"majiu",
                "south" : __DIR__"minju1",
                "west" : __DIR__"yongtai-nankou",
                "east" : __DIR__"huarui2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}