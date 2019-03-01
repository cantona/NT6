// Room: /d/mobei/chulan.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "牲畜欄");
        set("long", @LONG
畜欄精心分成幾格，分別圈了幾頭牛羊，一邊的木樁上，還系了三
匹馬，圈欄中不時響起牛羊的叫聲，間或駿馬長嘶。一邊是間很破爛的
小茅草屋。門口，畜欄中都打掃得很幹凈。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
                "southwest" : __DIR__"byriver",
        ]));
        set("outdoors","mobei");
        set("coor/x", -190);
        set("coor/y", 5170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}