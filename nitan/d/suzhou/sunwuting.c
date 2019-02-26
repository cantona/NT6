// Room: /d/suzhou/sunwuting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "孫武亭");
        set("long", @LONG
在真娘幕後的土丘上，有一座小亭子，名為孫武亭。相傳春秋時，
兵家孫武曾在此訓練兩隊宮女，由吳王的兩個寵姬分別擔任隊長，由於
寵姬與宮女們不聽軍令，雖三令五申，仍置若罔聞，孫武遂下令，先斬
兩姬于軍前以整軍紀。後人遂築此亭。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"zhenniang",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}