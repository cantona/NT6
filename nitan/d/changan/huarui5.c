//Room: huarui5.c

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
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju5",
                "west" : "/d/changan/huarui4",
                "east" : "/d/changan/huarui6",
                "north" : "/d/changan/zahuopu",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}