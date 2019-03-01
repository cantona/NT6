#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "大門坎子");
        set("long", @LONG
這裡是沿江向東的古道，多為進山採參的參客所走，因此
也稱參路。前面一座小山截斷去路，為東去採參的第一道屏障
故被稱為大門坎子。西面是寬闊的鬆花江 (river)。鬆花江在
冬春時結冰可以通行，夏秋化凍你只好找船家幫忙了。
LONG);
        //set("arrive_room", "/d/guanwai/chuanchang");
        set("to", "/d/guanwai/chuanchang");
        set("need_dodge", 200);
        set("exits", ([
                "southeast"  : __DIR__"ermenkan",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "guanwai");
        setup();
        replace_program(RIVER);
}
