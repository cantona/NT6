inherit ROOM;

void create()
{
        set("short", "武場");
        set("long", @LONG
 這裏是雪山寺的大練武場，豎着好多木樁和沙袋，僧人們日常均
在此刻苦習武。往東走穿過整個大練武場就是廣場，西邊有個小庫房，
南邊一大片開闊地，就是雪山聞名海內的祭壇。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "east" : __DIR__"chang2",
                "west" : __DIR__"kufang",
                "north" : __DIR__"chang3",
                "south" : __DIR__"jitan",
        ]));

        set("objects", ([
                __DIR__"npc/x_lama" : 1,
                    "/clone/npc/mu-ren" : 4,
        ]));

        setup();

        replace_program(ROOM);
}