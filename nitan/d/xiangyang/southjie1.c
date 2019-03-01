// Room: /d/xiangyang/southjie1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向南北兩頭延伸。南邊就是朱雀門，
北面是中央廣場，西面是錢莊，東面是襄陽城內的唯一一家學堂。雖
然襄陽戰火不斷，你仍能聽到學堂裡傳來學生們朗朗地讀書聲。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"xuetang",
                "west"  : __DIR__"qianzhuang",
                "south" : __DIR__"southjie2",
                "north" : __DIR__"guangchang",
        ]));
        set("coor/x", -7820);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}