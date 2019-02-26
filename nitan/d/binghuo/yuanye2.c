// Room: /binghuo/yuanye2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "原野");
        set("long", @LONG
平野上一羣梅花鹿正在低頭吃草，極目四望，除了那火山有些駭
人之外，周圍一片平靜，絕無可怖之處。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"yuanye1",
                "north"  : __DIR__"yuanye3",
        ]));
        setup();
        replace_program(ROOM);
}
