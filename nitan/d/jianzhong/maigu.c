#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","獨孤求敗埋骨之洞");
        set("long",@LONG
這洞其實甚淺，行不到三丈，已抵盡頭。洞中除了一張石桌和一
張石凳外就別無他物了。洞角有一堆亂石高起，極似一個墳墓，巖壁
上刻着三行字道：
    「縱橫江湖三十餘載，殺盡仇寇，敗盡英雄，天下更無抗手，無
可奈何，惟隱居深谷，以雕為友。嗚呼，生平求一敵手而不可得，誠
寂寥難堪也。
                                         劍魔獨孤求敗。」
LONG
        );
        set("exits",([
                "south":__DIR__"shandong1",
        ]));
        set("coor/x", -400);
        set("coor/y", -430);
        set("coor/z", 0);
        setup();
}
void init()
{
        object me=this_player();
        set_temp("dugu_visit", 1, me);
}        