inherit ROOM;

void create()
{
        set("short", "藥舖帳房");
        set("long", @LONG
這裡就是藥舖帳房，藥舖的巫老板正坐在太師椅上抽大煙
呢。藥舖的帳房先生巫攀冰在一旁忙著算帳。看著裡面一大堆
的帳本，你想要是那收來的錢是我的可就好了。
LONG);
        set("objects", ([
                  __DIR__"npc/wupanbing" : 1,
        ]));
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"yaopu",
        ]));

        set("coor/x", -9030);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}