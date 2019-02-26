//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "漢陽街");
        set ("long", @LONG
這是武漢最繁華的街道。從大江南北來的各色人等，熙熙攘攘，摩
肩接踵。西邊是一家小吃店，門口的招簾上寫着“老通城”三個大字。
東邊是一個碼頭。你側耳細聽，可以聽到江水拍打江岸的濤聲。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"matou1",
                "west" : __DIR__"laotc",
                "south": __DIR__"zhongxin",
                "north": __DIR__"hzjie1",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}