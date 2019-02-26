// Room: /d/suzhou/qianrenshi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "千人石");
        set("long", @LONG
在虎丘山中心，有一塊千人石，巨石呈暗紫紅色，由南向北傾斜石
面甚平坦，石壁如斧削。傳説吳王墓築成後，其子夫差怕泄露築墓祕密
假借墓成祝酒觀舞之名，將千餘名工匠全部殺戮，鮮血滲透石中，成暗
紅色。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"erxianting",
                "west"      : __DIR__"disanquan",
                "north"     : __DIR__"shijianshi",
                "northwest" : __DIR__"zhishuang",
                "southwest" : __DIR__"jianchi",
        ]));
	set("coor/x", 1100);
	set("coor/y", -1040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}