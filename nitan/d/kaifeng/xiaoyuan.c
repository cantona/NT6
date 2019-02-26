inherit ROOM;

void create()
{
        set("short", "小院");
        set("long", @LONG
你一腳踏進來，不由得喊了聲好，只見修篁一片，間中是兩棵佛
祖曾在其下悟道的菩提樹。小路沿着修竹而彎，北面路的盡頭就是方
丈大師傅的住所，也是他平常接待貴客的地方。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"fangzhang",
                  "west" : __DIR__"cangjing",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}