// Room: /d/luoyang/road10.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。道路兩邊，是一
排排高樹。樹林之外，便是一片片的農田了。田地裡傳來農人的呼號，
幾頭黃牛悠閒的趴臥著。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"road9",
                "west" : __DIR__"road11",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6880);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}