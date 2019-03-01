//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "漢川街");
        set ("long", @LONG
這是武漢最繁華的街道。從大江南北來的各色人等，熙熙攘攘，摩
肩接踵。東邊是一家客棧，西邊是賣藥材的店舖，似乎有人在炮制中藥，
傳來一陣陣舂石臼的聲音。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"zhongxin",
                "west" : __DIR__"ximen",
                "south": __DIR__"kedian",
                "north": __DIR__"yaocaidian",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5100);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}