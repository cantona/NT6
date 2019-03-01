// shandong.c
// Java Oct.10 1998

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
在這小山洞(dong)的深處，一股強大的水流自地上流出，形成一條
小河流向洞外。如果想再進一步深入的話，就得要跳入水中了。往外可
到小河邊。往裡就要潛水了。
LONG
        );
        set("item_desc", ([
                "dong" : "一個深邃、幽暗、恐怖的小山洞。\n",
        ]));
        set("exits", ([
                "out"       : __DIR__"xiaohebian",
                "southdown" : "/d/gumu/anhe2",
        ]));

        set("coor/x", -3160);
        set("coor/y", -10);
        set("coor/z", -10);
        setup();
}
int valid_leave(object me, string dir)
{
        if( dir == "southdown" && query("family/family_name", me) != "古墓派" )
        {
                return notify_fail("這麼急的水，你想跳下去自殺呀？\n");
        }
        if( dir == "southdown" && query("family/family_name", me) == "古墓派" )
        {
                message_vision(HIG "$N縱身一躍，跳入水潭之中。\n"NOR,me);
                write(HIC"許多遊魚從你邊遊過，你伸手一撈，卻抓了空。突然你眼前一亮，一股暗流撲面而來，將你沖入一個所在。\n"NOR);
                return 1;
        }
        return ::valid_leave(me, dir);
}