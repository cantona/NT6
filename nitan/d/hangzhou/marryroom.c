// marry_room.c
#include <room.h>
inherit ROOM;
string look_zhaopai(object me);
void create()
{
        set("short", "紅娘莊");
        set("long", @LONG
你現在正站在風光秀麗的西子湖畔的紅娘莊裏，臨水憑窗，隔着
碧綠的湖面，就是斷橋了。紅娘莊並不大，但這裏卻主天下之悲歡離
合，成就所有天下有情人。
    靠近門口的地方有一塊烏木雕成的招牌(zhaopai)。
LONG);
        set("exits", ([
            "east" : __DIR__"road10",
        ]) );
        set("item_desc", ([
            "zhaopai": (: look_zhaopai :),
        ]) );
        set("objects", ([
            __DIR__"npc/hongniang" : 1,
            __DIR__"npc/meipo" : 1,
        ]) );
        set("no_steal",1);
        set("no_clean_up", 0);
	set("coor/x", 820);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
}

string look_zhaopai(object me)
{
        return "締結(marry)或解除(unmarry)婚約。\n";
}
