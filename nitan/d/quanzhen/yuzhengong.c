// yuzhengong.c 遇真宮
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "遇真宮");
        set("long", @LONG
這裡是重陽宮以前的舊址，是王重陽王真人參悟大道之前清修的
地方。後來手創全真教後，此地的布局實在太小，就將重陽宮遷到東
面山上，將此地重新改名為遇真宮，以紀念得道之意。這裡很久沒有
人來過了，桌椅上都積滿了灰塵。
LONG
        );
        set("exits", ([
                "south" : __DIR__"fangzhenqiao",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", 150);
        set("coor/z", 190);
        setup();
        replace_program(ROOM);
}