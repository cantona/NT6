//  Room: /d/luoyang/road11.c

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。道路兩邊，是一
排排高樹。樹林之外，便是一片片的農田了。大道往東通向脂粉之都的
揚州，而西面則是通往洛陽城。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"road10",
                "west" : __DIR__"road0",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6890);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}