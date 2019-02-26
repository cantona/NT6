// Room: /d/huijiang/zhangpeng.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "帳篷");
        set("long", @LONG
這個牛皮帳篷大約能容十多人。地上鋪着華麗的地毯，上面繡着美
麗的花紋，邊上拖着流蘇。毯子中間擺着果盆。邊上是幾個大的箱子，
一邊還橫着把鐵背弓。
LONG );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/muzhuolun": 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"buluo1",
        ]));
        set("coor/x", -50040);
        set("coor/y", 9050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}