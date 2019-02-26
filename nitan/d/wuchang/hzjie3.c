//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "漢正街");
        set ("long", @LONG
這是武漢最繁華的街道。從大江南北來的各色人等，熙熙攘攘，摩
肩接踵。西邊一個大棚子裏擺放了許多菊花，奼紫嫣紅，令人歎為觀止。
東邊是有名的琴台。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"qintai",
                "west" : __DIR__"juhuahui",
                "south": __DIR__"hzjie5",
                "north": __DIR__"zhongxin",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}