// /guanwai/songhuajiang.c

inherit ROOM;

void create()
{
        set("short", "松花江面");
        set("long", @LONG
這裏是松花江的江面，冰面早已解凍，清澈的江水濤濤北去，兩岸是如
煙如霧鬆支，柳條。船伕悠閒地在船尾把着舵。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        setup();
        replace_program(ROOM);
}