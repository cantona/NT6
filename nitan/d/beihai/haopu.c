// /d/beihai/haopu.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "濠濮間");
        set("long", @LONG
東岸之濠濮澗，為三間水榭。北鄰畫舫齋，東北有迭砌玲瓏的山石
環繞。在嶙峋山石間有一泓池水，池中有敞軒、曲橋、迴旋變化於咫尺
之內，頗具自然之趣。
LONG
        );
        set("exits", ([
                "northwest" : __DIR__"huafang",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -150);
        set("coor/y", 4080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}