// Room: tanggate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "唐門大門");
        set("long", @LONG
這裡就是名聞天下的唐門的大門(gate)。唐門建的十分巍峨，青
牆碧瓦下的銅包大門緊緊關閉，兩邊唐門弟子一溜排開，這個架勢看
來是不好進去了。
LONG );
        set("outdoors", "chengdu");
        set("no_fight",1);
        set("exits", ([
                "north"  : __DIR__"northroad2",
        ]));
        set("objects", ([
                __DIR__"npc/tangdun" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}