#include <ansi.h>
inherit BUILD_ROOM;

int do_qian(string arg);

void create()
{
        set("short", "寒水潭");
        set("long", @LONG
這裏是草地的邊緣，青草已經很稀疏了，仍然有些許玉蜂飛過尋
覓食物。不遠處是一個清波盪漾的大水潭 (tan)，水很清，隱約可以
見過水底的怪石嶙峋，一二游魚倏地從水底遊過，又不知道躲到哪塊
石頭後面藏身去了。陽光映照下，水面泛起了一道七色彩虹，望着這
般美景，你俗念盡消。
LONG );
        set("outdoors", "quanzhen");
        set("max_room", 3);
        set("exits", ([
                "northwest" : __DIR__"caodi2",
        ]));
        set("objects", ([
                "/d/gumu/npc/yufeng" : random(5),
        ]));

        set("item_desc", ([
                "tan": HIW "\n一口很深的水攤，不知道可不可以潛(qian)下到這水底世界去？\n"NOR,
        ]) );
        set("coor/x", -3200);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_qian", "qian");
}


int do_qian(string arg)
{
        object me=this_player();

        if (! arg || arg != "tan" )
                return notify_fail("你要往哪裏潛水？\n");

        message_sort(HIG "$N縱身一躍，跳入水攤之中，許多游魚從"
                     "你身邊遊過，你伸手一撈，卻抓了空。突然$N "
                     HIG "眼前一亮，一股暗流撲面而來，將$N" HIG
                     "衝入一個所在。\n" NOR,this_player());

        me->move(__DIR__"mishi");
        return 1;
}
