inherit ROOM;

void create()
{
        set("short", "當舖");
        set("long", @LONG
這是一家坐落在京城王府井大街西邊的當舖。這家當舖規模不大，
但是素來以買賣公平著稱，京城的百姓遇手緊的情況時，都會把東西
拿到這裡來典當。一個五尺高的木制櫃台擋在你的面前，櫃台上擺著
一個牌子 (paizi)，櫃台後坐著當舖的老板，一雙精明的眼睛上上下
下打量著你。
LONG );
        set("no_fight", 1);
        set("no_beg",1);
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        賣 
buy         買
pawn        當
expiate     贖
value       估價
",
        ]));

        set("objects", ([
                "/d/beijing/npc/dangpuzhang" : 1,
        ]));
        set("exits", ([
                "west" : "/d/beijing/wang_6",
        ]));

	set("coor/x", -2760);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}