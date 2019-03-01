// /d/xiakedao/shiroom16.c 俠客島 石室16

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
進門便聽得急促的呼吸之聲。只見一人面向石壁(wall)而坐，肩
頭聳動，喘息連連，似是練功到了緊要關頭。另一名大漢雙掌按在前
人的後心，頭頂也是白氣氤氲。
LONG );
        set("exits", ([
                "east"  : __DIR__"shihole4",
        ]));
        set("item_desc", ([
                "wall" : @WALL
這面牆卻另有奇處，「意氣素霓生」幾個大字在最下面。其上刻的是
幾個唐裝舞女，姿態柔順輕盈。側面斜斜的一行注：白樂天詩：漁陽
鼙鼓動地來，驚破霓裳羽衣曲。另一行注字跡潦草：至柔而動也剛。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3100);
        set("coor/y", -25400);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"