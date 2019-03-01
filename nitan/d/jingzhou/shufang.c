//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "書房");
        set ("long", @LONG
這是知府大人的書房。左面是一排書架，放著荊州府志，以及各種
各樣的古書舊錄。右面是一個古色古香的雕花木架，擺放了酒觴銅鼎，
金銀玉器等各色古玩。正中一張大方桌，上面整齊地排列著文房四寶。
東邊是一個走廊，南邊是一個花圃，隱約可以聞到陣陣花的迷香。
LONG);
        set("exits", ([
                "west" : __DIR__"huayuan",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}