// Room: /d/yueyang/xijie.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "西街");
        set("long", @LONG
這是一條又長又寬的青石大道，馬匹馳過，得得有聲。行道兩邊一
些稀稀落落的樹蔭下，或坐或臥躺了些衣衫不整的人。岳陽為天下丐幫
總舵的常駐地，街面上三三兩兩的，乞丐成群往來不絕。各地的客商也
多來此蹭活。
    南面是個廣場。北面是一棟大屋。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"zhongxin",
                "west"  : __DIR__"ximen",
                "south" : __DIR__"guangchang",
                "north" : __DIR__"gaibanggate",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/chen-guyan" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
	set("coor/x", -6210);
	set("coor/y", -3010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}