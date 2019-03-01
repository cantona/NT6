// Room: /d/shaolin/bagua4.c
// Date: YZC 96/01/19

inherit ROOM;

#include "/d/shaolin/bagua.h"

void create()
{
        set("short", "八卦陣");
        set("long", @LONG
這是便是八卦陣，四壁全由粗糙的片巖壘垛而成。巨石猙獰，缺
口及合縫處犬牙交錯，如洪荒怪獸，其勢似欲擇人而噬。壁上刻著一
行小篆：『八卦通天地，金剛泣鬼神』。四周灰塵厚積，蛛網密布，
看來已久無人行。地上似乎躺著幾具屍體，早已腐爛化灰，腳步經過，
連屍首身上的衣物也隨風飄散。
LONG );
        set("exits", ([
                "乾" : __DIR__"bagua7",
                "巽" : __DIR__"bagua6",
                "離" : __DIR__"bagua5",
                "艮" : __DIR__"bagua4",
                "兌" : __DIR__"bagua3",
                "坎" : __DIR__"bagua2",
                "震" : __DIR__"bagua1",
                "坤" : __DIR__"bagua0",
        ]));
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (check_dirs(me, dir))
                return notify_fail("你踩動了機關，掉進僧監。\n");
        return ::valid_leave(me, dir);
}
