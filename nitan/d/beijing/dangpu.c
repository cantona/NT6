inherit ROOM;

void create()
{
        set("short", "當鋪");
        set("long", @LONG
這是一家坐落在京城王府井大街西邊的當鋪。這家當鋪規模不大，
但是素來以買賣公平著稱，京城的百姓遇手緊的情況時，都會把東西
拿到這裏來典當。一個五尺高的木製櫃枱擋在你的面前，櫃枱上擺着
一個牌子 (paizi)，櫃枱後坐着當鋪的老闆，一雙精明的眼睛上上下
下打量着你。
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