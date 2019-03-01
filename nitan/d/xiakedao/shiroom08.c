// /d/xiakedao/shiroom08.c 俠客島 石室8

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
石洞正中，一位白眉僧人和一位青袍之人正比試武功。一對男女
在旁邊並肩奔行，趨退之際，步法配合甚是和諧。另有一人神色不屑
地站在牆角，邊指點石壁(wall)，邊指摘眾人的招式。
LONG );
        set("exits", ([
                "east" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻著「深藏身與名」幾個大字。字的下方刻的是一個膾炙
人口的故事：范蠡與西施功成身退，泛舟湖上。只見圖中美女星目含
情，旁邊是范大夫微笑不語。舟下的水紋盪漾，與遠方天色連成一體。
WALL
        ]));
        set("objects", ([
                __DIR__"master/huang" : 1,
                __DIR__"master/yideng" : 1,
        ]));
/*
一燈大師哈哈大笑，對著黃藥師拱了拱手道：老爺子過獎了!
一燈大師說道：勁力內含，發之無形，傷人與不覺之中。

一燈大師“□”地沖到黃藥師的跟前，左手無名指一反一復連點兩下，旋即退開，正是一式
「陰陽交錯」！
黃藥師身形疾閃，使出一招“海燕騰空”，身體如同為海風所激，向後飄開一丈有余，避過
一燈大師攻擊。

一燈大師身形陡然向上拔起，雙手急點數下，一式「烈日驕陽」已將黃藥師的全身要穴罩在
指風之下！
黃藥師身形疾閃，使出一招“海燕騰空”，身體如同為海風所激，向後飄開一丈有余，避過
一燈大師攻擊。
*/
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3100);
        set("coor/y", -25200);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"