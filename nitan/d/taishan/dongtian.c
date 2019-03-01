// Room: /d/taishan/dongtian.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "東天門");
        set("long", @LONG
日觀峰東邊為東天門，雙石如門，是岱頂的東面出口。往東為伏虎
門，峽口陡險。下為鷹愁澗，水東北流，入洗鶴灣。澗東岸北崖古洞深
敞，名清靜石屋，元初女道冠孫清靜曾在此修真。此處川林僻曠，塵跡
罕至，俗呼仙人場。其北為空明山，中穴通明，午時日光穿照。 
LONG );
        set("exits", ([
                "west" : __DIR__"riguanroad2",
                "up"   : "/d/reborn/jitan1",
        ]));
        set("objects", ([
                CLASS_D("taishan")+"/yuyinzi" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 80);
	set("coor/y", 300);
	set("coor/z", 190);
	setup();
        replace_program(ROOM);
}