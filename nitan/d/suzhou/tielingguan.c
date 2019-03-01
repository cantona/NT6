// Room: /d/suzhou/tielingguan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "鐵嶺關");
        set("long", @LONG
關呈長方形，磚石結構，正中的三層敵樓為新建。鐵嶺關地處水陸
要沖登敵樓，既可了望，又能放炮射箭。這關垣、運河、石橋所組成的
聯合工事，當時是為了防御合抵抗侵擾的倭寇。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"fengqiao",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));
	set("coor/x", 1050);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}