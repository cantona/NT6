// /d/xiakedao/shiroom07.c 俠客島 石室7

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏亦有數人研習武功。幾名女子都顯得頗有心得，面色凝重地
對照着石壁(wall)練習步法，旁邊的兩個白衣青年卻滿臉迷惑，似乎
未窺門徑。
LONG );
        set("exits", ([
                "west" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「事了拂衣去」幾個大字。字的下方刻的是林中的一
名女子，長髮披肩，背向而立。林中也有霧氣環繞。旁有注云：小徑
紅衿，終無計留住。另一行注：拂者，柔中之力。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25200);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"