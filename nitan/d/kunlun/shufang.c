// Room: /d/kunlun/shufang.c
// Last Modified by Winder on Nov. 15 2000

inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這裏是書房，靠牆一排大書架，擺放着很多的書籍，崑崙三聖何足
道以琴棋而號稱以“聖”，故崑崙派一直引以為榮，鼓勵弟子學琴棋藝。
一眼望過去，似乎有關於不少琴棋方面的書。
LONG );
        set("exits", ([
                "west"  : __DIR__"jiuqulang3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -119970);
        set("coor/y", 40100);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}