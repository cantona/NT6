//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "漢正街");
        set ("long", @LONG
這是武漢最繁華的街道。從大江南北來的各色人等，熙熙攘攘，摩
肩接踵。西邊是一家雜貨店，東邊是一座寺院。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"guiyuansi",
                "west" : __DIR__"zahuodian",
                "north": __DIR__"hzjie3",
                "south": __DIR__"nanmen",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}