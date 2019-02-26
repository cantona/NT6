// Room: /d/huijiang/zhangpeng3.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "帳篷");
        set("long", @LONG
這頂粗牛皮帳篷看來很久沒打掃了，在靠近地面的部分，有好幾個
被老鼠咬穿的小洞，一張用羊皮拼起來的毯子擺在帳篷的中心，蓬壁掛
着的弓箭旁靠着把長鐵搶，尖端發出白色的亮光。
LONG );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/huoayi" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"buluo2",
        ]));
        set("coor/x", -50060);
        set("coor/y", 9060);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}