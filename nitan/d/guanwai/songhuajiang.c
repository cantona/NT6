// /guanwai/songhuajiang.c

inherit ROOM;

void create()
{
        set("short", "鬆花江面");
        set("long", @LONG
這裡是鬆花江的江面，冰面早已解凍，清澈的江水濤濤北去，兩岸是如
煙如霧鬆支，柳條。船夫悠閒地在船尾把著舵。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        setup();
        replace_program(ROOM);
}