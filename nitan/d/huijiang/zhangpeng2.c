// Room: /d/huijiang/zhangpeng2.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set ("short", "帳篷");
        set ("long", @LONG
這是頂草草加工的牛皮帳篷，地上鋪着張氈子，看來已經很破舊了，
不過洗刷得很乾淨。一邊的箱子上放着個小小的紅色盒子，除此之外，帳
篷中就一個白鐵水壺和兩個水碗。
LONG);
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"buluo2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50040);
        set("coor/y", 9060);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}