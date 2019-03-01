#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
山中樹木茂密，花開萬朵，這裡風景秀美，小鳥在喳喳地叫著，
陽光從樹頁的縫隙中照進來，形成五彩的斑斕，你的心情不由的高興
起來，跟著小鳥的歌聲，向前走去。
LONG );
        set("exits", ([
                "northeast" : __DIR__"road3",
                "westup" : __DIR__"qingshan2",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -330);
        set("coor/y", -190);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
