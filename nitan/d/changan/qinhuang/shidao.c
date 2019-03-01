// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "石道");
        set("long", @LONG
石道兩旁的石獸由原本代表帝皇的獅子，變成了象徵疆域廣闊的
駱駝，然後是四靈之首的麒麟，再是喻意武功昌盛、南征北討的戰馬，
跟著是羊頭牛尾，頂生獨角的獬獸。
LONG );
    set("exits", ([
       "north" :__DIR__"shidao1",
       "south" :__DIR__"shendao",
]));
    setup();
    replace_program(ROOM);
}