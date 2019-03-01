// Room: /d/huangshan/sanhua.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "散花塢");
        set("long", @LONG
散花塢乃是一寬谷，谷中峰巒參差，筆架峰，駱駝石等錯列其間，
遠觀峰巒疊嶂，近顧怪石獻巧。每當春夏之季，花卉盛開，更是繁花似
錦，其中天女花最為奇艷。此花九瓣，潔白清雅遍布山塢，引人注目，
故稱“散花塢”。清代程之□有詩讚曰：“何來仙女散天花？原是天都
仙子家。一塢花香分兩度，爭傳秋實與春華。”
    東面便是著名的怪石夢筆生花。
LONG
        );
        set("exits", ([ 
                "west"      : __DIR__"paiyun",
                "east"      : __DIR__"mengbi",
                "northeast" : __DIR__"shisun",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -1020);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}