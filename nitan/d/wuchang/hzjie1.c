//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "漢陽街");
        set ("long", @LONG
這是武漢最繁華的街道。從大江南北來的各色人等，熙熙攘攘，摩
肩接踵。西邊是一家錢莊，可以聽到叮叮噹噹的金銀聲音。東邊是一
座酒樓，門額上懸掛一方橫匾，“四季美”三字擦得閃閃發亮，陣陣酒
肉的香味傳來。北邊是條大驛道。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"sijimei",
                "west" : __DIR__"qianzhuang",
                "south": __DIR__"hzjie2",
                "north": __DIR__"beimen",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}