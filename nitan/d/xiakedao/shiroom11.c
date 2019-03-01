// /d/xiakedao/shishi11.c 俠客島 石室11

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
進門便覺得室中潮氣極重，呼吸不暢，想來是深入山腹之故。數
人也是或坐或立，默不做聲地各自研習武功,火把卻不知為何少了幾
支，石壁(wall)上投下了大片陰影。
LONG );
        set("exits", ([
                "west"  : __DIR__"shihole3",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「將炙啖朱亥」幾個大字。字的下方刻的是信陵君拜
訪朱亥的故事。傳説那朱亥殺豬為生，畫中之人袒胸持刀，滿臉剽悍
之色。魏公子無忌在一旁站立，神色恭謹。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25300);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"