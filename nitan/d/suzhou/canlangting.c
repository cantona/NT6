// Room: /d/suzhou/canlangting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "滄浪亭");
        set("long", @LONG
滄浪亭在蘇州的北大街南側，因為環境相對幽雅，使得男女老少都
喜愛在這裏閒庭散步。在亭中放眼望去，四周一片碧綠的草坪，亭子翼
然於聳翠之中，飛檐凌空琵琶形牌科，佈滿檐口四周，亭上的額匾和石
柱上的楹聯(lian)使人更加喜愛這裏。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("item_desc", ([
                "lian" :
"清風明月本無價 近水遠山皆有情\n",
        ]));
        set("exits", ([
                "southeast" : __DIR__"dongdajie1",
                "southwest" : __DIR__"xidajie1",
                "north"     : __DIR__"beidajie1",
                "south"     : __DIR__"baodaiqiao",
                //"east"      : __DIR__"hong-damen",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}