inherit ROOM;

void create()
{
        set("short", "武場");
        set("long", @LONG
 這裡是雪山寺的大練武場，樹著好多木樁和沙袋，僧人們日常均
在此刻苦習武。往東就是廣場，西邊一直穿過大連武場有個小庫房。
LONG );
        set("outdoors", "xueshan");

        set("exits", ([
                "east" : __DIR__"guangchang",
                "west" : __DIR__"chang",
        ]));

        set("objects", ([
                __DIR__"npc/x_lama" : 1,
        ]));

        setup();
        replace_program(ROOM);
}