// /d/xiakedao/shiroom22.c 俠客島 石室22

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
只聽劈啪之聲不斷，兩個長臉漢子各持齊眉棍，正自印證武功。
一旁的兩人卻是默不作聲，以指作棍，在空中虛點虛刺。一名少女斜
倚石壁(wall)，甚是疲倦，右側長衫男子端着一盤點心，神色關注。
LONG );
        set("exits", ([
                "north" : __DIR__"shihole6",
                ]));
       set("item_desc", ([
                "wall" : @WALL
牆上「不慚世上英」幾個大字自左上斜至右下。右上及左下各繪兩幅
小圖，均是手持棍棒的人形，並無故事。圖側及大字之間亦是密佈小
注。一行注云：心慚混沌。又一行注：象曰：元吉在上，大有慶也。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25610);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"