//tianweitang.c
inherit ROOM;

void create()
{
        set("short", "天市堂");
        set("long", @LONG
你一進入明教的天市堂，頓時感到一鼓肅殺之氣。教眾出入都十
分小心，惟恐驚動了坐在油木桌後的堂主李天垣。見你進來李天垣抬
眼看了看你，一張很柔和的臉卻立馬讓你心驚肉跳。
LONG );
        set("exits", ([
                "west"  : __DIR__"tianweitang",
        ]));
        set("objects",([
             __DIR__"npc/litianyuan":1,
             __DIR__"npc/yinwulu":1,
        ]));
        setup();
        replace_program(ROOM);
}