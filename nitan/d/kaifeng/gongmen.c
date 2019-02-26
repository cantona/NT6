inherit ROOM;

void create()
{
        set("short", "石拱門");
        set("long", @LONG
用石頭搭起來的一個拱門，高越兩丈，上面鏤刻雲紋。兩邊是拴
馬的石柱。再往前邊一點的地方，有塊旗杆石，那是由兩塊巨大的石
頭，一半埋到地下，在和口的地方，有個大孔可以插旗杆。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southup" : __DIR__"8bao",
                  "northdown" : __DIR__"road",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}