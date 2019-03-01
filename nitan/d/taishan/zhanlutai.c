// Room: /d/taishan/zhanlutai.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "瞻魯台");
        set("long", @LONG
愛身崖上有巨石突兀，高約丈許，石旁大書“瞻魯台”，俗稱幡桿
石。傳孔子曾登此瞻魯都曲阜。
LONG );
        set("exits", ([
                "down" : __DIR__"aishen",
        ]));
        set("objects", ([
                WEAPON_DIR+"sword/houjian" : random(2)+1,
                WEAPON_DIR+"sword/mujian" : random(2)+1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 290);
	set("coor/z", 220);
	setup();
        replace_program(ROOM);
}