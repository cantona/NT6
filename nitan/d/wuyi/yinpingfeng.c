// Room: /d/wuyi/yinpingfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "隱屏峯");
        set("long", @LONG
這裏是隱屏峯北側。巖壁上三個蒼勁大字“仙凡界”，標示了天界
與人間的界定。由“步虛”二字處攀鐵梯，饒“雞胸”，便是“仙凡界”
了。沿石梯向上，過清代汪痴頤坐化的“痴頤窩”，盤上“龍脊”，直
達峯頂。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "westdown" : __DIR__"yunwo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -5010);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
