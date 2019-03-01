// Room: /d/huanggong/wumen.c

inherit ROOM;

void create()
{
        set("short", "午門");
        set("long", @LONG
午門是紫禁城的正門，是皇帝送軍出征和受降的地方。五丈高的暗
紅色城牆上，建有五座崇樓，因此俗稱“五鳳樓”。台上正中是個大門
樓，進深五間，面闊九間，呈“九五”格局。下有五個門洞，重檐廡殿
頂。城門主樓凹進，兩翼張出，東西四座重檐四角攢頂式方形闕亭，以
十三廊廡聯接，輔翼著正樓，形如雁翅，氣勢巍峨。
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"dao10",
                "east"  : __DIR__"dao1",
                "south" : __DIR__"dianwai",
                "north" : __DIR__"taihemen",
        ]));
        set("objects", ([
                __DIR__"npc/yulin" : 2,
                __DIR__"npc/fuchun" : 1,
        ]));

	set("coor/x", -2800);
	set("coor/y", 7701);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}