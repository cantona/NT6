// Room: /d/quanzhou/houshanmen.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "後山門");
        set("long", @LONG
走到藏經閣後，東北邊有扇小門。這就是開元寺的後山門。門外是
個城隍廟。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southup"     : __DIR__"cangjingge",
                "northeast"   : __DIR__"chenghuangmiao",
        ]));
	set("coor/x", -930);
	set("coor/y", -7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}