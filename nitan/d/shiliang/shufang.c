// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "書房");
        set("long", @LONG
温家的書房很大，牆邊擺滿了一書架一書架的書，一張書桌上
放着文房四寶，檀香正燃着，屋內充滿了那種神祕的香氣，其實温
氏五老都是草莽出身，平時難得到這裏一次。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ 
                "west" : __DIR__"zoulang7",
        ]));
        set("coor/x", 1630);
        set("coor/y", -1920);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}