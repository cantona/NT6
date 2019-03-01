// Room: /d/lingzhou/yushanfang.c

inherit ROOM;

void create()
{
        set("short", "御膳房");
        set("long", @LONG
這裡是膳房，西廂房是兩位江南名廚的住處，東廂房是膳房下手們
住的。北面是柴房。院子打掃的很幹凈，中間有一口水井。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
                "west"  : __DIR__"huilang",
                "south" : __DIR__"bingku",
                "north" : __DIR__"chaifang",
        ]));
        set("no_clean_up", 0);
        set("resource", ([ /* sizeof() == 1 */
                "water" : 1,
        ]));

        set("coor/x", -6265);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}