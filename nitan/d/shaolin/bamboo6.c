// Room: /d/shaolin/bamboo6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
這是一片密密的竹林。這裏人跡罕至，惟聞足底叩擊路面，有僧
敲木魚聲；微風吹拂竹葉，又如簌簌禪唱。令人塵心為之一滌，真是
絕佳的禪修所在。
LONG );
        set("exits", ([
                "west" : __DIR__"bamboo"+(random(13)+1),
                "north" : __DIR__"bamboo7",
                "south" : __DIR__"bamboo"+(random(13)+1),
                "east" : __DIR__"bamboo"+(random(13)+1),
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "east")addn_temp("bamboo/count", 1, me);
        else addn_temp("bamboo/count", -1, me);

        return ::valid_leave(me, dir);
}
