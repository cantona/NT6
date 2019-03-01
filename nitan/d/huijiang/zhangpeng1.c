// Room: /d/huijiang/zhangpeng1.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "帳篷");
        set("long", @LONG
一頂華麗小巧的帳篷，舖著華麗的地毯，中間是張小矮幾，兩端的
幾腳鏤刻成巧妙的花紋，上面擺著個花瓶，插了幾枝野花，一面青銅鏡
子就掛在帳篷的邊上，看得出是個姑娘的住所。
LONG );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/huoqingtong" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"buluo1",
        ]));
        set("coor/x", -50060);
        set("coor/y", 9050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}