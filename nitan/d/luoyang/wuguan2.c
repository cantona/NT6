inherit ROOM;

void create()
{
        set("short", "武館後院");
        set("long", @LONG
這裏是武館的後院，龍騰武館的館主經常會在這裏親自向一些年輕有
為的弟子傳授武功，得到他的指點你會受益匪淺。一個方方正正的大院子，
環境比較幽靜，並不像外面那麼喧譁，吵鬧，是一個靜心練武的好地方。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wuguan",
        ]));

	set("coor/x", -7010);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}