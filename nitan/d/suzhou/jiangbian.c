// Room: /d/suzhou/jiangbian.c
// Last Modified by Winder on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "江邊");
        set("long",@long
這條江叫做曹娥江。相傳漢和帝時，這裏有一名巫者，名叫曹盱，
能婆娑樂神。五月五日，醉舞舟中，墮江而死。其女年十四歲，繞江啼
哭七晝夜，跳入波中。後五日，負父之屍浮於江面，里人葬之江邊，故
名。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"tulu2",
                "south"     : __DIR__"caoebei",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1030);
	set("coor/y", -1090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}