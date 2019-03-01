// Room: /d/suzhou/disanquan.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short","第三泉");
        set("long",@LONG
第三泉再千人石之西得鐵華巖下，此泉晶瑩醇厚，系唐代茶聖陸羽
所挖，故名“陸羽井”，品定為天下第三泉，井上有三泉亭。崖題“鐵
華巖”三字，取蘇軾詩“鐵華秀巖壁”句意。
LONG);
        set("outdoors", "suzhou");
        set("exits",([
                "east" :__DIR__"qianrenshi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1090);
	set("coor/y", -1040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}