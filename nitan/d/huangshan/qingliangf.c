// Room: /d/huangshan/qingliangf.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "清涼峯");
        set("long", @LONG
清涼台上行就是清涼峯，峯頂平坦，有一塊著名巧石，形似猴子，
雲霧時節，雲海茫茫，便是“猴子觀海”了，一旦雲開天朗時候，又叫
“猴子望太平”。望太平，是因為猴子正前方是舊時的太平縣。
LONG
        );
        set("exits", ([ 
                "eastdown" : __DIR__"qingliang",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}